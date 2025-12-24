//
// Created by Johny Georges on 2025-12-19.
//

#include "free-struct-ref-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string FreeStructRefIRFunction::getFreeStructRefIRFunctionName() {
    return "jet.free.struct.ref";
}

void FreeStructRefIRFunction::declareFreeStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeStructRefIRFunction::getFreeStructRefIRFunctionName(), irModuleNode->getModule());
}

void FreeStructRefIRFunction::generateFreeStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto structRefType = irGenerator->generateIRStructRefType();

    auto function = irModuleNode->getFreeStructRefFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto freeStructIfBlock = irGenerator->generateIfBlock(irContext);
    auto freeStructIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto freeStructElseBlock = irGenerator->generateIfElseBlock(irContext);
    auto freeStructEndBlock = irGenerator->generateIfEndBlock(irContext);

    auto structIndex = structRefType->getStructIndex();
    auto counterIndex = structRefType->getCounterIndex();

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), counterIndex);
    auto refCounterPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefCounterPointer);
    auto currentRefCount = functionBlock->getBuilder()->get()->CreateLoad(structRefType->getCounterIRType()->getType(), refCounterPointer, "currentRefCount");
    DebugIRInjectorHelper::injectLog(functionBlock, "CURRENT STRUCT REF COUNT", irGenerator->getInjector(), irModuleNode);
    DebugIRInjectorHelper::injectLog(functionBlock, currentRefCount, irGenerator->getInjector(), irModuleNode);
    functionBlock->getBuilder()->get()->CreateBr(freeStructIfBlock->getBlock());

    auto isLastRef = freeStructIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLE,
            currentRefCount,
            irGenerator->generateIntConstant(1)
    );
    freeStructIfBlock->getBuilder()->get()->CreateCondBr(isLastRef, freeStructIfThenBlock->getBlock(), freeStructElseBlock->getBlock());


    auto structTypePointer = freeStructIfThenBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getAllocIndex() });
    auto loadedStructType = freeStructIfThenBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), structTypePointer);
    auto pointerToStructPointer = freeStructIfThenBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), structIndex);
    auto structPointer = freeStructIfThenBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToStructPointer);
    DebugIRInjectorHelper::injectLog(freeStructIfThenBlock, "FREEING STRUCT!", irGenerator->getInjector(), irModuleNode);
    freeStructIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeStructFunction(),
            { structPointer, loadedStructType }
    );
//    freeStructIfThenBlock->getBuilder()->get()->CreateCall(
//            irContext->getIRModule()->getMallocFreeFunction(),
//            { refCounterPointer }
//    );
    DebugIRInjectorHelper::injectLog(freeStructIfThenBlock, "DONE FREEING STRUCT!", irGenerator->getInjector(), irModuleNode);
    freeStructIfThenBlock->getBuilder()->get()->CreateBr(freeStructEndBlock->getBlock());

//    DebugIRInjectorHelper::injectLog(freeStructElseBlock, "DID NOT FREE STRUCT SINCE STRUCT REF COUNT != 0", irGenerator->getInjector(), irModuleNode);
    freeStructElseBlock->getBuilder()->get()->CreateBr(freeStructEndBlock->getBlock());
    freeStructEndBlock->addVoidReturn();
}