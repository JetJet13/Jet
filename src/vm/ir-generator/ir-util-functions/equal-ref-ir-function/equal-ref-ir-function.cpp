//
// Created by Johny Georges on 2025-10-13.
//

#include "equal-ref-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string EqualRefIRFunction::getEqualRefIRFunctionName() {
    return "jet.equal.ref";
}

std::string EqualRefIRFunction::getEqualRefLeftOnlyIRFunctionName() {
    return "jet.equal.ref.left.only";
}

std::string EqualRefIRFunction::getEqualRefRightOnlyIRFunctionName() {
    return "jet.equal.ref.right.only";
}

void EqualRefIRFunction::declareEqualRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType, typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualRefIRFunction::getEqualRefIRFunctionName(), irModuleNode->getModule()->get());
}

void EqualRefIRFunction::declareEqualRefLeftOnlyFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType, typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualRefIRFunction::getEqualRefLeftOnlyIRFunctionName(), irModuleNode->getModule()->get());
}

void EqualRefIRFunction::declareEqualRefRightOnlyFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType, typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualRefIRFunction::getEqualRefRightOnlyIRFunctionName(), irModuleNode->getModule()->get());
}

void EqualRefIRFunction::generateEqualRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto irRefType = irGenerator->generateIrRefType(irGenerator->generateVoidType());
    auto function = irModuleNode->getEqualRefFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto firstRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), function->getArg(0), irRefType->getRefValueIndex());
    auto firstRefValue = InstructionIRInjectorHelper::injectLoad(pointerType, firstRefValuePointer, functionBlock);
    auto secondRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), function->getArg(1), irRefType->getRefValueIndex());
    auto secondRefValue = InstructionIRInjectorHelper::injectLoad(pointerType, secondRefValuePointer, functionBlock);
    auto pointerToUnderlyingTypeValue = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), typeValueType->getAllocIndex());
    auto underlyingTypeValue = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), pointerToUnderlyingTypeValue, functionBlock);
    functionBlock->getBuilder()->get()->CreateRet(
        functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getEqualValueFunction(),
            {
                firstRefValue,
                secondRefValue,
                underlyingTypeValue,
                underlyingTypeValue
            }
        )
    );

}

void EqualRefIRFunction::generateEqualRefLeftOnlyFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto irRefType = irGenerator->generateIrRefType(irGenerator->generateVoidType());
    auto function = irModuleNode->getEqualRefLeftOnlyFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto firstRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), function->getArg(0), irRefType->getRefValueIndex());
    auto firstRefValue = InstructionIRInjectorHelper::injectLoad(pointerType, firstRefValuePointer, functionBlock);
    auto pointerToUnderlyingTypeValue = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), typeValueType->getAllocIndex());
    auto underlyingTypeValue = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), pointerToUnderlyingTypeValue, functionBlock);
    functionBlock->getBuilder()->get()->CreateRet(
        functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getEqualValueFunction(),
            {
                firstRefValue,
                function->getArg(1),
                underlyingTypeValue,
                underlyingTypeValue
            }
        )
    );
}

void EqualRefIRFunction::generateEqualRefRightOnlyFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto irRefType = irGenerator->generateIrRefType(irGenerator->generateVoidType());
    auto function = irModuleNode->getEqualRefRightOnlyFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto secondRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), function->getArg(1), irRefType->getRefValueIndex());
    auto secondRefValue = InstructionIRInjectorHelper::injectLoad(pointerType, secondRefValuePointer, functionBlock);
    auto pointerToUnderlyingTypeValue = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), typeValueType->getAllocIndex());
    auto underlyingTypeValue = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), pointerToUnderlyingTypeValue, functionBlock);
    functionBlock->getBuilder()->get()->CreateRet(
        functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getEqualValueFunction(),
            {
                function->getArg(0),
                secondRefValue,
                underlyingTypeValue,
                underlyingTypeValue
            }
        )
    );

}