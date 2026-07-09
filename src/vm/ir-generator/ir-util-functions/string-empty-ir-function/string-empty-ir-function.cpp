//
// Created by Johny Georges on 2026-03-23.
//

#include "string-empty-ir-function.h"

std::string StringEmptyIRFunction::getStringEmptyIRFunctionName() {
    return "jet.string.empty";
}

void StringEmptyIRFunction::generateStringEmptyFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto boolType = irGenerator->generateBooleanType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto zero = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto functionType = llvm::FunctionType::get(boolType, { pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringEmptyIRFunction::getStringEmptyIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isNumElementsOneIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isNumElementsOneIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->createChild();
    auto successorBlock = functionBlock->getLastChildOrSelf();
    auto pointerToNumElements = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zero, numElementsIndex });
    auto loadedNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToNumElements);
    functionBlock->getBuilder()->get()->CreateBr(isNumElementsOneIfBlock->getBlock());

    // it needs to be 1 instead of 0 to account for terminator char '\0'
    auto isNumElementsOne = isNumElementsOneIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            loadedNumElements,
            irGenerator->generateIntConstant(1)
    );
    isNumElementsOneIfBlock->getBuilder()->get()->CreateCondBr(isNumElementsOne, isNumElementsOneIfThenBlock->getBlock(), successorBlock->getBlock());
    isNumElementsOneIfThenBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(true));
    successorBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(false));
}