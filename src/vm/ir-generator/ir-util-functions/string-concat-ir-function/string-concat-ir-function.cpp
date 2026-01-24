//
// Created by Johny Georges on 2026-01-07.
//

#include "string-concat-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string StringConcatIRFunction::getStringConcatIRFunctionName() {
    return "jet.string.concat";
}

void StringConcatIRFunction::generateStringConcatFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateIRCharType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateIRCharType());

    auto functionType = llvm::FunctionType::get(arrayPointerType->getType(),
                                                { pointerType->getType(), pointerType->getType() },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringConcatIRFunction::getStringConcatIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto firstStringNumElementsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getNumElementsIndex());
    auto loadedFirstStringNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, firstStringNumElementsPointer);
    auto secondStringNumElementsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(1), arrayPointerType->getNumElementsIndex());
    auto loadedSecondStringNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, secondStringNumElementsPointer);

    // ignore \0 character appended to all strings
    auto firstStringNumElements = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Sub,
            loadedFirstStringNumElements,
            irGenerator->generateIntConstant(1)
    );
    auto newStringNumElements = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            firstStringNumElements,
            loadedSecondStringNumElements
    );

    auto newStringMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { newStringNumElements, irGenerator->generateInt64Constant(charType->getSizeInBytes()) }
    );

    auto pointerToFirstStringAllocation = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedPointerToFirstString = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToFirstStringAllocation);

    auto charAlignment = charType->getAlignment();
    functionBlock->getBuilder()->get()->CreateMemCpy(
        newStringMalloc,
        charAlignment,
        loadedPointerToFirstString,
        charAlignment,
        firstStringNumElements
    );

    auto pointerToSecondStringAllocation = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(1), arrayPointerType->getAllocIndex());
    auto loadedPointerToSecondString = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToSecondStringAllocation);
    auto newStringMallocFirstStringOffsetPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(charType->getType(), newStringMalloc, { firstStringNumElements });
    functionBlock->getBuilder()->get()->CreateMemCpy(
            newStringMallocFirstStringOffsetPointer,
            charAlignment,
            loadedPointerToSecondString,
            charAlignment,
            loadedSecondStringNumElements
    );
    auto arrayPointerAllocation = functionBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            functionBlock,
            arrayPointerType,
            newStringNumElements,
            irGenerator->generateIntConstant(1),
            arrayPointerAllocation,
            newStringMalloc
    );
    auto loadedStringPointer = functionBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), arrayPointerAllocation);
    functionBlock->getBuilder()->get()->CreateRet(loadedStringPointer);

}