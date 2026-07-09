//
// Created by Johny Georges on 2025-12-05.
//

#include "free-captured-variable-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../../../types/ir-type-id.h"

std::string FreeCapturedVariableIRFunction::getFreeCapturedVariableIRFunctionName() {
    return "jet.free.captured.variable";
}

void FreeCapturedVariableIRFunction::declareFreeCapturedVariableFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                           FreeCapturedVariableIRFunction::getFreeCapturedVariableIRFunctionName(), irModuleNode->getModule()->get());
}

void FreeCapturedVariableIRFunction::generateFreeCapturedVariableFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto capturedVariableType = irGenerator->generateIRCapturedVariableType(pointerType);

    auto function = irModuleNode->getFreeCapturedVariableFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    DebugIRInjectorHelper::injectLog(functionBlock, "FREEING CAPTURED VARIABLE!", irGenerator->getInjector(), irModuleNode);
    auto pointerToCaptureCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(capturedVariableType->getType(), function->getArg(0), capturedVariableType->getCaptureCounterIndex());
    auto captureCounterPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToCaptureCounterPointer);
    auto currentCaptureCount = functionBlock->getBuilder()->get()->CreateLoad(capturedVariableType->getCaptureCounterIRType()->getType(), captureCounterPointer, "currentCaptureCount");

    auto freeVariableIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "free.variable.");
    auto freeVariableIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "free.variable.");
    auto freeCaptureCounterIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto freeCaptureCounterIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto freeVariableElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    auto freeVariableEndBlock = irGenerator->generateIfEndBlock(irContext, functionBlock->getScope());

    functionBlock->getBuilder()->get()->CreateBr(freeVariableIfBlock->getBlock());

    auto isCaptureCountOne = freeVariableIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            currentCaptureCount,
            irGenerator->generateIntConstant(1)
    );
    freeVariableIfBlock->getBuilder()->get()->CreateCondBr(isCaptureCountOne, freeVariableIfThenBlock->getBlock(), freeVariableElseBlock->getBlock());

    auto underlyingTypePointer = freeVariableIfThenBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), {typeValueType->getAllocIndex() });
    auto loadedUnderlyingType = freeVariableIfThenBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), underlyingTypePointer);
    auto capturedVariableTypeId = freeVariableIfThenBlock->getBuilder()->get()->CreateExtractValue(loadedUnderlyingType, {typeValueType->getIdIndex() });
    auto pointerToCapturedVariablePointer = freeVariableIfThenBlock->getBuilder()->get()->CreateStructGEP(capturedVariableType->getType(), function->getArg(0), capturedVariableType->getVariableIndex());
    auto capturedVariablePointer = freeVariableIfThenBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToCapturedVariablePointer);

    freeVariableIfThenBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getFreeValueFunction(),
        { capturedVariablePointer, loadedUnderlyingType }
    );
    freeVariableIfThenBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getMallocFreeFunction(),
        { capturedVariablePointer }
    );
    freeVariableIfThenBlock->getBuilder()->get()->CreateBr(freeCaptureCounterIfBlock->getBlock());

    auto isCapturedVariableNotStructRef = freeCaptureCounterIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_NE,
            capturedVariableTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    auto isCapturedVariableNotLambda = freeCaptureCounterIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_NE,
            capturedVariableTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.INVOCABLE)
    );
    auto isCapturedVariableNotStructRefAndNotLambda = freeCaptureCounterIfBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::And,
            isCapturedVariableNotStructRef,
            isCapturedVariableNotLambda
    );
    freeCaptureCounterIfBlock->getBuilder()->get()->CreateCondBr(isCapturedVariableNotStructRefAndNotLambda, freeCaptureCounterIfThenBlock->getBlock(), freeVariableEndBlock->getBlock());
    freeCaptureCounterIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFreeFunction(),
            { captureCounterPointer }
    );
    freeCaptureCounterIfThenBlock->getBuilder()->get()->CreateBr(freeVariableEndBlock->getBlock());
    
    auto newCaptureCount = freeVariableElseBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Sub,
            currentCaptureCount,
            irGenerator->generateIntConstant(1)
    );
    freeVariableElseBlock->getBuilder()->get()->CreateStore(newCaptureCount, captureCounterPointer);
    DebugIRInjectorHelper::injectLog(freeVariableElseBlock, currentCaptureCount, irGenerator->getInjector(), irModuleNode);
    DebugIRInjectorHelper::injectLog(freeVariableElseBlock, "DECREMENTED CAPTURED VARIABLE COUNT!", irGenerator->getInjector(), irModuleNode);
    freeVariableElseBlock->getBuilder()->get()->CreateBr(freeVariableEndBlock->getBlock());
    DebugIRInjectorHelper::injectLog(freeVariableEndBlock, "FREEING CAPTURED VARIABLE DONE!", irGenerator->getInjector(), irModuleNode);
    freeVariableEndBlock->addVoidReturn();
}