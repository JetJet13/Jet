//
// Created by Johny Georges on 2025-12-10.
//

#include "free-lambda-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string FreeLambdaIRFunction::getFreeLambdaIRFunctionName() {
    return "jet.free.lambda";
}

void FreeLambdaIRFunction::declareFreeLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeLambdaIRFunction::getFreeLambdaIRFunctionName(), irModuleNode->getModule());
}

void FreeLambdaIRFunction::generateFreeLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto irFunctionParameterType = new IRFunctionParameterType(
        irGenerator->getFunctionParameterType(),
        pointerType,
        irGenerator->generateIRFunctionParameterCleanupType(),
        new IRLambdaParameterListType(),
        irGenerator->generateVoidType()
    );

    auto function = irModuleNode->getFreeLambdaFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToLambdaScope = functionBlock->getBuilder()->get()->CreateStructGEP(irFunctionParameterType->getType(), function->getArg(0), irFunctionParameterType->getFunctionScopeArgumentIndex());
    auto loadedLambdaScope = InstructionIRInjectorHelper::injectLoad(irFunctionParameterType->getFunctionScopeArgumentType(), pointerToLambdaScope, functionBlock);
    auto pointerToCleanupFunction = functionBlock->getBuilder()->get()->CreateStructGEP(irFunctionParameterType->getType(), function->getArg(0), irFunctionParameterType->getFunctionCleanupIndex());
    auto loadedCleanupFunction = InstructionIRInjectorHelper::injectLoad(irFunctionParameterType->getFunctionCleanupType(), pointerToCleanupFunction, functionBlock);
    functionBlock->getBuilder()->get()->CreateCall(
            irFunctionParameterType->getCleanupFunctionType(),
            loadedCleanupFunction,
            {
                loadedLambdaScope
            }
    );
    functionBlock->addVoidReturn();
}