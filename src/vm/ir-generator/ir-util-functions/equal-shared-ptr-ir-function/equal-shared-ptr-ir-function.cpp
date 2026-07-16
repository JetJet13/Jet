//
// Created by Johny Georges on 2025-10-13.
//

#include "equal-shared-ptr-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string EqualSharedPtrIRFunction::getEqualSharedPtrIRFunctionName() {
    return "jet.equal.ref";
}

std::string EqualSharedPtrIRFunction::getEqualSharedPtrLeftOnlyIRFunctionName() {
    return "jet.equal.ref.left.only";
}

std::string EqualSharedPtrIRFunction::getEqualSharedPtrRightOnlyIRFunctionName() {
    return "jet.equal.ref.right.only";
}

void EqualSharedPtrIRFunction::declareEqualSharedPtrFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType, typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualSharedPtrIRFunction::getEqualSharedPtrIRFunctionName(), irModuleNode->getModule()->get());
}

void EqualSharedPtrIRFunction::declareEqualSharedPtrLeftOnlyFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType, typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualSharedPtrIRFunction::getEqualSharedPtrLeftOnlyIRFunctionName(), irModuleNode->getModule()->get());
}

void EqualSharedPtrIRFunction::declareEqualSharedPtrRightOnlyFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType, typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualSharedPtrIRFunction::getEqualSharedPtrRightOnlyIRFunctionName(), irModuleNode->getModule()->get());
}

void EqualSharedPtrIRFunction::generateEqualSharedPtrFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto sharedPtrType = irGenerator->generateIrSharedPtrType(irGenerator->generateVoidType());
    auto function = irModuleNode->getEqualSharedPtrFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);

    auto firstRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(0), sharedPtrType->getSharedValueIndex());
    auto firstRefValue = InstructionIRInjectorHelper::injectLoad(pointerType, firstRefValuePointer, functionBlock);
    auto secondRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(1), sharedPtrType->getSharedValueIndex());
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

void EqualSharedPtrIRFunction::generateEqualSharedPtrLeftOnlyFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto irSharedPtrType = irGenerator->generateIrSharedPtrType(irGenerator->generateVoidType());
    auto function = irModuleNode->getEqualSharedPtrLeftOnlyFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);

    auto firstRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), function->getArg(0), irSharedPtrType->getSharedValueIndex());
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

void EqualSharedPtrIRFunction::generateEqualSharedPtrRightOnlyFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto irSharedPtrType = irGenerator->generateIrSharedPtrType(irGenerator->generateVoidType());
    auto function = irModuleNode->getEqualSharedPtrRightOnlyFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);

    auto secondRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), function->getArg(1), irSharedPtrType->getSharedValueIndex());
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