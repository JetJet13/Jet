//
// Created by Johny Georges on 2025-12-19.
//

#include "free-struct-ref-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string FreeStructRefIRFunction::getFreeStructRefIRFunctionName() {
    return "jet.free.struct.ref";
}

void FreeStructRefIRFunction::declareFreeStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeStructRefIRFunction::getFreeStructRefIRFunctionName(), irModuleNode->getModule()->get());
}

void FreeStructRefIRFunction::generateFreeStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto structRefType = irGenerator->generateIRStructRefType();

    auto function = irModuleNode->getFreeStructRefFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);

    auto freeStructRefIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto freeStructRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto freeStructRefElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    auto freeStructRefEndBlock = irGenerator->generateIfEndBlock(irContext, functionBlock->getScope());

    auto structIndex = structRefType->getStructIndex();
    auto counterIndex = structRefType->getCounterIndex();

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), counterIndex);
    auto refCounterPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefCounterPointer);
    auto currentRefCount = functionBlock->getBuilder()->get()->CreateLoad(structRefType->getCounterIRType()->getType(), refCounterPointer, "currentRefCount");
    DebugIRInjectorHelper::injectLog(functionBlock, "CURRENT STRUCT REF COUNT", irGenerator->getInjector(), irModuleNode);
    DebugIRInjectorHelper::injectLog(functionBlock, currentRefCount, irGenerator->getInjector(), irModuleNode);
    functionBlock->getBuilder()->get()->CreateBr(freeStructRefIfBlock->getBlock());

    auto isLastRef = freeStructRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLE,
            currentRefCount,
            irGenerator->generateIntConstant(1)
    );
    freeStructRefIfBlock->getBuilder()->get()->CreateCondBr(isLastRef, freeStructRefIfThenBlock->getBlock(), freeStructRefElseBlock->getBlock());

    auto structTypePointer = freeStructRefIfThenBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), {typeValueType->getAllocIndex() });
    auto loadedStructType = freeStructRefIfThenBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), structTypePointer);
    auto pointerToStructPointer = freeStructRefIfThenBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), structIndex);
    auto structPointer = freeStructRefIfThenBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToStructPointer);
    DebugIRInjectorHelper::injectLog(freeStructRefIfThenBlock, "FREEING STRUCT!", irGenerator->getInjector(), irModuleNode);
    freeStructRefIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeStructFunction(),
            { structPointer, loadedStructType }
    );
    freeStructRefIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFreeFunction(),
            { structPointer }
    );
    DebugIRInjectorHelper::injectLog(freeStructRefIfThenBlock, "FREEING STRUCT REF COUNTER!", irGenerator->getInjector(), irModuleNode);
    freeStructRefIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFreeFunction(),
            { refCounterPointer }
    );
    DebugIRInjectorHelper::injectLog(freeStructRefIfThenBlock, "DONE FREEING STRUCT!", irGenerator->getInjector(), irModuleNode);
    freeStructRefIfThenBlock->getBuilder()->get()->CreateBr(freeStructRefEndBlock->getBlock());

    freeStructRefElseBlock->getBuilder()->get()->CreateBr(freeStructRefEndBlock->getBlock());
    freeStructRefEndBlock->addVoidReturn();
}