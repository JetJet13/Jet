//
// Created by Johny Georges on 2025-07-05.
//

#include "array-size-ir-function.h"

std::string ArraySizeIRFunction::getArraySizeIRFunctionName() {
    return "jet.array.size";
}

void ArraySizeIRFunction::generateArraySizeFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto zero = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto functionType = llvm::FunctionType::get(intType,
                                                { pointerType->getType() },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArraySizeIRFunction::getArraySizeIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto pointerToNumElements = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zero, numElementsIndex });
    auto loadedNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToNumElements);
    functionBlock->getBuilder()->get()->CreateRet(loadedNumElements);
}