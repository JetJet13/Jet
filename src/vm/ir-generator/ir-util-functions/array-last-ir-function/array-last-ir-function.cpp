//
// Created by Johny Georges on 2025-05-31.
//

#include "array-last-ir-function.h"

std::string ArrayLastIRFunction::getArrayLastIRFunctionName() {
    return "jet.array.last";
}

void ArrayLastIRFunction::generateArrayLastFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto zero = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
                                                { pointerType->getType(), intType },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayLastIRFunction::getArrayLastIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto pointerToNumElements = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zero, numElementsIndex });
    auto loadedNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToNumElements);
    auto lastElementIndex = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Sub,
            loadedNumElements,
            irGenerator->generateIntConstant(1)
    );
    auto lastElement = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getArrayAccessFunction()->getFunctionType(),
            irModuleNode->getArrayAccessFunction(),
            { function->getArg(0), lastElementIndex, function->getArg(1) }
    );
    functionBlock->getBuilder()->get()->CreateRet(lastElement);
}