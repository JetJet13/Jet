//
// Created by Johny Georges on 2025-12-05.
//

#include "free-captured-variable-ir-function.h"

std::string FreeCapturedVariableIRFunction::getFreeCapturedVariableIRFunctionName() {
    return "jet.free.captured.variable";
}

void FreeCapturedVariableIRFunction::declareFreeCapturedVariableFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                           FreeCapturedVariableIRFunction::getFreeCapturedVariableIRFunctionName(), irModuleNode->getModule());
}

void FreeCapturedVariableIRFunction::generateFreeCapturedVariableFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto capturedVariableType = irGenerator->generateIRCapturedVariableType(pointerType);

    auto function = irModuleNode->getFreeCapturedVariableFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto pointerToCaptureCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(capturedVariableType->getType(), function->getArg(0), capturedVariableType->getCaptureCounterIndex());
    auto captureCounterPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToCaptureCounterPointer);
    auto currentCaptureCount = functionBlock->getBuilder()->get()->CreateLoad(capturedVariableType->getCaptureCounterIRType()->getType(), captureCounterPointer, "currentCaptureCount");

    auto freeVariableIfBlock = irGenerator->generateIfBlock(irContext, "free.variable.");
    auto freeVariableIfThenBlock = irGenerator->generateIfThenBlock(irContext, "free.variable.");
    auto freeVariableElseBlock = irGenerator->generateIfElseBlock(irContext);
    auto freeVariableEndBlock = irGenerator->generateIfEndBlock(irContext);

    functionBlock->getBuilder()->get()->CreateBr(freeVariableIfBlock->getBlock());

    auto isCaptureCountOne = freeVariableIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            currentCaptureCount,
            irGenerator->generateIntConstant(1)
    );
    freeVariableIfBlock->getBuilder()->get()->CreateCondBr(isCaptureCountOne, freeVariableIfThenBlock->getBlock(), freeVariableElseBlock->getBlock());

    auto underlyingTypePointer = freeVariableIfThenBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), {typeValueType->getAllocIndex() });
    auto loadedUnderlyingType = freeVariableIfThenBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), underlyingTypePointer);
    auto pointerToCapturedVariablePointer = freeVariableIfThenBlock->getBuilder()->get()->CreateStructGEP(capturedVariableType->getType(), function->getArg(0), capturedVariableType->getVariableIndex());
    auto capturedVariablePointer = freeVariableIfThenBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToCapturedVariablePointer);

    freeVariableIfThenBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getFreeValueFunction()->getFunctionType(),
        irContext->getIRModule()->getFreeValueFunction(),
        { capturedVariablePointer, loadedUnderlyingType }
    );
    freeVariableIfThenBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getMallocFreeFunction()->getFunctionType(),
        irContext->getIRModule()->getMallocFreeFunction(),
        { captureCounterPointer }
    );
    freeVariableIfThenBlock->getBuilder()->get()->CreateBr(freeVariableEndBlock->getBlock());

    auto newCaptureCount = freeVariableElseBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Sub,
            currentCaptureCount,
            irGenerator->generateIntConstant(1)
    );
    freeVariableElseBlock->getBuilder()->get()->CreateStore(newCaptureCount, captureCounterPointer);
    freeVariableElseBlock->getBuilder()->get()->CreateBr(freeVariableEndBlock->getBlock());
    freeVariableEndBlock->addVoidReturn();
}