//
// Created by Johny Georges on 2026-03-23.
//

#include "string-last-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string StringLastIRFunction::getStringLastIRFunctionName() {
    return "jet.string.last";
}

void StringLastIRFunction::generateStringLastFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateIRCharType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto sizeInBytes = irGenerator->generateIntConstant(charType->getSizeInBytes());
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringLastIRFunction::getStringLastIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNumElementsOneIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isNumElementsOneIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isNumElementsOneIfElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    functionBlock->createSuccessor();
    auto successorBlock = functionBlock->getLastSuccessorOrSelf();
    auto pointerToNumElements = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getNumElementsIndex());
    auto loadedNumElements = InstructionIRInjectorHelper::injectLoad(intType, pointerToNumElements, functionBlock);
    auto offsetIndexAllocation = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    functionBlock->getBuilder()->get()->CreateBr(isNumElementsOneIfBlock->getBlock());

    // it needs to be 1 instead of 0 to account for terminator char '\0'
    auto isNumElementsOne = isNumElementsOneIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            loadedNumElements,
            irGenerator->generateIntConstant(1)
    );
    isNumElementsOneIfBlock->getBuilder()->get()->CreateCondBr(isNumElementsOne, isNumElementsOneIfThenBlock->getBlock(), isNumElementsOneIfElseBlock->getBlock());

    isNumElementsOneIfThenBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(1), offsetIndexAllocation);
    isNumElementsOneIfThenBlock->getBuilder()->get()->CreateBr(successorBlock->getBlock());

    auto twoLessNumElements = isNumElementsOneIfElseBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Sub,
            loadedNumElements,
            irGenerator->generateIntConstant(2)
    );
    isNumElementsOneIfElseBlock->getBuilder()->get()->CreateStore(twoLessNumElements, offsetIndexAllocation);
    isNumElementsOneIfElseBlock->getBuilder()->get()->CreateBr(successorBlock->getBlock());

    auto loadedOffsetIndex = InstructionIRInjectorHelper::injectLoad(intType, offsetIndexAllocation, successorBlock);
    auto byteOffset = successorBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Mul,
            loadedOffsetIndex,
            sizeInBytes
    );
    auto pointerToString = successorBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedString = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToString);
    auto pointerToLastElement = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, loadedString, { byteOffset });
    successorBlock->getBuilder()->get()->CreateRet(pointerToLastElement);
}