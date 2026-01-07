//
// Created by Johny Georges on 2025-12-10.
//

#include "copy-lambda-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string CopyLambdaIRFunction::getCopyLambdaIRFunctionName() {
    return "jet.copy.lambda";
}

void CopyLambdaIRFunction::declareCopyLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyLambdaIRFunction::getCopyLambdaIRFunctionName(), irModuleNode->getModule());
}

void CopyLambdaIRFunction::generateCopyLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto intType = irGenerator->generateIntType();
    auto irInvocableType = irGenerator->generateIRInvocableType();

    auto function = irModuleNode->getCopyLambdaFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToNewLambdaFunction = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getFunctionIndex());
    auto pointerToLambdaFunctionPointer = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(1),  irInvocableType->getFunctionIndex());
    auto loadedPointerToLambdaFunctionPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToLambdaFunctionPointer);
    InstructionIRInjectorHelper::injectStore(loadedPointerToLambdaFunctionPointer, pointerToNewLambdaFunction, functionBlock);

    auto pointerToNewLambdaScopeArgument = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getFunctionScopeArgumentIndex());
    auto pointerToLambdaScopeArgument = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(1),  irInvocableType->getFunctionScopeArgumentIndex());
    auto loadedPointerToLambdaScopeArgument = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToLambdaScopeArgument);
    InstructionIRInjectorHelper::injectStore(loadedPointerToLambdaScopeArgument, pointerToNewLambdaScopeArgument, functionBlock);

    auto pointerToNewLambdaCounter = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getFunctionRefCounterIndex());
    auto pointerToLambdaCounter = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(1),  irInvocableType->getFunctionRefCounterIndex());
    auto loadedPointerToLambdaCounter = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToLambdaCounter);
    InstructionIRInjectorHelper::injectStore(loadedPointerToLambdaCounter, pointerToNewLambdaCounter, functionBlock);

    auto pointerToNewLambdaCleanupFunction = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getFunctionCleanupIndex());
    auto pointerToLambdaCleanupFunction = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(1),  irInvocableType->getFunctionCleanupIndex());
    auto loadedPointerToLambdaCleanupFunction = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToLambdaCleanupFunction);
    InstructionIRInjectorHelper::injectStore(loadedPointerToLambdaCleanupFunction, pointerToNewLambdaCleanupFunction, functionBlock);

    auto currentLambdaCount = InstructionIRInjectorHelper::injectLoad(intType, loadedPointerToLambdaCounter, functionBlock);
    auto newLambdaCount = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            currentLambdaCount,
            irGenerator->generateIntConstant(1)
    );
    InstructionIRInjectorHelper::injectStore(newLambdaCount, loadedPointerToLambdaCounter, functionBlock);

    functionBlock->addVoidReturn();
}