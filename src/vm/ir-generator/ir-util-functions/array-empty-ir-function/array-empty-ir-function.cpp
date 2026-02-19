//
// Created by Johny Georges on 2025-07-05.
//

#include "array-empty-ir-function.h"

std::string ArrayEmptyIRFunction::getArrayEmptyIRFunctionName() {
    return "jet.array.empty";
}

void ArrayEmptyIRFunction::generateArrayEmptyFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto boolType = irGenerator->generateBooleanType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto zero = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto functionType = llvm::FunctionType::get(boolType, { pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayEmptyIRFunction::getArrayEmptyIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNumElementsZeroIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isNumElementsZeroIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->createSuccessor();
    auto successorBlock = functionBlock->getLastSuccessorOrSelf();
    auto pointerToNumElements = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zero, numElementsIndex });
    auto loadedNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToNumElements);
    functionBlock->getBuilder()->get()->CreateBr(isNumElementsZeroIfBlock->getBlock());

    auto isNumElementsZero = isNumElementsZeroIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            loadedNumElements,
            irGenerator->generateIntConstant(0)
    );
    isNumElementsZeroIfBlock->getBuilder()->get()->CreateCondBr(isNumElementsZero, isNumElementsZeroIfThenBlock->getBlock(), successorBlock->getBlock());
    isNumElementsZeroIfThenBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(true));
    successorBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(false));
}