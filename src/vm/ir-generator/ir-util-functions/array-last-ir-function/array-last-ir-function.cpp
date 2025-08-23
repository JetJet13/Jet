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
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto zero = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
                                                { pointerType->getType(), typeValueType->getType() },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayLastIRFunction::getArrayLastIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto sizeInBytesIndex = irGenerator->generateIntConstant(typeValueType->getSizeInBytesIndex());
    auto arrayElementTypeValue = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getAllocIndex() }, "arrayElementTypeValue");
    auto arrayElementSizeInBytesPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), arrayElementTypeValue, { zeroIndex, sizeInBytesIndex });
    auto sizeInBytes = functionBlock->getBuilder()->get()->CreateLoad(intType, arrayElementSizeInBytesPointer, "sizeInBytes");
    auto pointerToNumElements = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zero, numElementsIndex });
    auto loadedNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToNumElements);
    auto oneLessNumElements = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Sub,
            loadedNumElements,
            irGenerator->generateIntConstant(1)
    );
    auto byteOffset = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Mul,
            oneLessNumElements,
            sizeInBytes
    );
    auto pointerToArray = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zero, allocIndex });
    auto loadedArray = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToArray);
    auto pointerToLastElement = functionBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, loadedArray, { byteOffset });
    functionBlock->getBuilder()->get()->CreateRet(pointerToLastElement);
}