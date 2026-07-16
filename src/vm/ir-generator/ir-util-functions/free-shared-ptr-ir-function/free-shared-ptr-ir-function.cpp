//
// Created by Johny Georges on 2025-05-14.
//

#include "free-shared-ptr-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../../../types/ir-type-id.h"

std::string FreeSharedPtrIRFunction::getFreeSharedPtrIRFunctionName() {
    return "jet.free.shared.ptr";
}

void FreeSharedPtrIRFunction::declareFreeSharedPtrFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeSharedPtrIRFunction::getFreeSharedPtrIRFunctionName(), irModuleNode->getModule()->get());
}

void FreeSharedPtrIRFunction::generateFreeSharedPtrFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto refType = irGenerator->generateIrRefType(pointerType);

    auto function = irModuleNode->getFreeSharedPtrFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);

    auto freeValueIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto freeValueIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto freeValueElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    auto freeValueEndBlock = irGenerator->generateIfEndBlock(irContext, functionBlock->getScope());

    auto refValueIndex = refType->getRefValueIndex();
    auto refCounterIndex = refType->getRefCounterIndex();

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refCounterIndex);
    auto refCounterPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefCounterPointer);
    auto currentRefCount = functionBlock->getBuilder()->get()->CreateLoad(refType->getRefCounterIRType()->getType(), refCounterPointer, "currentRefCount");
    DebugIRInjectorHelper::injectLog(functionBlock, currentRefCount, irGenerator->getInjector(), irModuleNode);
    functionBlock->getBuilder()->get()->CreateBr(freeValueIfBlock->getBlock());

    auto isLastRef = freeValueIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            currentRefCount,
            irGenerator->generateIntConstant(1)
    );
    freeValueIfBlock->getBuilder()->get()->CreateCondBr(isLastRef, freeValueIfThenBlock->getBlock(), freeValueElseBlock->getBlock());


    auto underlyingTypePointer = freeValueIfThenBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getAllocIndex() });
    auto loadedUnderlyingType = freeValueIfThenBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), underlyingTypePointer);
    auto pointerToRefValuePointer = freeValueIfThenBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refValueIndex);
    auto refValuePointer = freeValueIfThenBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefValuePointer);
    freeValueIfThenBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getFreeValueFunction(),
        { refValuePointer, loadedUnderlyingType }
    );
    freeValueIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFreeFunction(),
            { refValuePointer }
    );
    DebugIRInjectorHelper::injectLog(freeValueIfThenBlock, "FREEING REF COUNTER!", irGenerator->getInjector(), irModuleNode);
    freeValueIfThenBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getMallocFreeFunction(),
        { refCounterPointer }
    );
    freeValueIfThenBlock->getBuilder()->get()->CreateBr(freeValueEndBlock->getBlock());

    auto newRefCount = freeValueElseBlock->getBuilder()->get()->CreateBinOp(
        llvm::Instruction::BinaryOps::Sub,
        currentRefCount,
        irGenerator->generateIntConstant(1)
    );
    freeValueElseBlock->getBuilder()->get()->CreateStore(newRefCount, refCounterPointer);
    DebugIRInjectorHelper::injectLog(freeValueElseBlock, "DECREMENTED REF COUNT!", irGenerator->getInjector(), irModuleNode);
    freeValueElseBlock->getBuilder()->get()->CreateBr(freeValueEndBlock->getBlock());
    freeValueEndBlock->addVoidReturn();
}