//
// Created by Johny Georges on 2026-01-21.
//

#include "equal-lambda-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string EqualLambdaIRFunction::getEqualLambdaIRFunctionName() {
    return "jet.equal.lambda";
}

void EqualLambdaIRFunction::declareEqualLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualLambdaIRFunction::getEqualLambdaIRFunctionName(), irModuleNode->getModule()->get());
}

void EqualLambdaIRFunction::generateEqualLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto irInvocableType = irGenerator->generateIRInvocableType();
    auto function = irModuleNode->getEqualLambdaFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto firstLambdaFunctionPointer = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getFunctionIndex());
    auto firstLambdaFunction = InstructionIRInjectorHelper::injectLoad(pointerType, firstLambdaFunctionPointer, functionBlock);
    auto secondLambdaFunctionPointer = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(1), irInvocableType->getFunctionIndex());
    auto secondLambdaFunction = InstructionIRInjectorHelper::injectLoad(pointerType, secondLambdaFunctionPointer, functionBlock);
    functionBlock->getBuilder()->get()->CreateRet(
        functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            firstLambdaFunction,
            secondLambdaFunction
        )
    );

}