//
// Created by Johny Georges on 2025-05-31.
//

#include "array-concat-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

std::string ArrayConcatIRFunction::getArrayConcatIRFunctionName() {
    return "jet.array.concat";
}

void ArrayConcatIRFunction::generateArrayConcatFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto zero = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
                                                { pointerType->getType(), pointerType->getType(), intType, intType },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayConcatIRFunction::getArrayConcatIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto firstArrayNumElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zero, numElementsIndex });
    auto loadedFirstArrayNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, firstArrayNumElementsPointer);
    auto secondArrayNumElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(1), { zero, numElementsIndex });
    auto loadedSecondArrayNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, secondArrayNumElementsPointer);
    auto newArrayNumElements = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            loadedFirstArrayNumElements,
            loadedSecondArrayNumElements
    );
    auto newArraySize = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                newArrayNumElements,
                function->getArg(2)
            }
    );
    auto newArrayMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction()->getFunctionType(),
            irModuleNode->getMallocFunction(),
            { newArraySize }
    );

    auto pointerToFirstArrayAllocation = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zero, allocIndex });
    auto loadedPointerToFirstArray = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToFirstArrayAllocation);
    auto firstArraySize = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                    loadedFirstArrayNumElements,
                    function->getArg(2)
            }
    );
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction()->getFunctionType(),
            irModuleNode->getMemcpyFunction(),
            { newArrayMalloc, loadedPointerToFirstArray, firstArraySize }
    );

    auto pointerToSecondArrayAllocation = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(1), { zero, allocIndex });
    auto loadedPointerToSecondArray = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToSecondArrayAllocation);
    auto newArrayMallocFirstArrayOffsetPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, newArrayMalloc, { firstArraySize });
    auto secondArraySize = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                    loadedSecondArrayNumElements,
                    function->getArg(2)
            }
    );
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction()->getFunctionType(),
            irModuleNode->getMemcpyFunction(),
            { newArrayMallocFirstArrayOffsetPointer, loadedPointerToSecondArray, secondArraySize }
    );
    auto arrayPointerAllocation = functionBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            functionBlock,
            arrayPointerType,
            newArrayNumElements,
            function->getArg(3),
            arrayPointerAllocation,
            newArrayMalloc
    );
    auto loadedArrayPointer = functionBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), arrayPointerAllocation);
    functionBlock->getBuilder()->get()->CreateRet(loadedArrayPointer);

}