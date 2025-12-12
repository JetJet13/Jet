//
// Created by Johny Georges on 2025-05-14.
//

#include "free-ref-ir-function.h"

std::string FreeRefIRFunction::getFreeRefIRFunctionName() {
    return "jet.free.ref";
}

void FreeRefIRFunction::declareFreeRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeRefIRFunction::getFreeRefIRFunctionName(), irModuleNode->getModule());
}

void FreeRefIRFunction::generateFreeRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto refType = irGenerator->generateIrRefType(pointerType);

    auto function = irModuleNode->getFreeRefFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    functionBlock->addVoidReturn();

    auto refValueIndex = refType->getRefValueIndex();
    auto refCounterIndex = refType->getRefCounterIndex();
    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refCounterIndex);
    auto refCounterPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefCounterPointer);
    auto currentRefCount = functionBlock->getBuilder()->get()->CreateLoad(refType->getRefCounterIRType()->getType(), refCounterPointer, "currentRefCount");

    auto freeValueIfBlock = irGenerator->generateIfBlock(irContext, "string.");
    auto freeValueIfThenBlock = irGenerator->generateIfThenBlock(irContext, "string.");
    auto freeValueElseBlock = irGenerator->generateIfElseBlock(irContext);
    auto freeValueEndBlock = irGenerator->generateIfEndBlock(irContext);

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
        irContext->getIRModule()->getFreeValueFunction()->getFunctionType(),
        irContext->getIRModule()->getFreeValueFunction(),
        { refValuePointer, loadedUnderlyingType }
    );
    freeValueIfThenBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getMallocFreeFunction()->getFunctionType(),
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
    freeValueElseBlock->getBuilder()->get()->CreateBr(freeValueEndBlock->getBlock());

    freeValueEndBlock->addVoidReturn();
}