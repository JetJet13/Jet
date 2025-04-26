//
// Created by Johny Georges on 2024-09-26.
//

#include "copy-string-ir-function.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"

std::string CopyStringIRFunction::getCopyStringIRFunctionName() {
    return "jet.copy.string";
}

void CopyStringIRFunction::generateCopyStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = new IRType(irGenerator->generateCharType());
    auto pointerType = irGenerator->generatePointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(charType);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());

    auto functionType = llvm::FunctionType::get(llvm::Type::getVoidTy(**context), { pointerType, pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyStringIRFunction::getCopyStringIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto pointerToSourceStringNumChars = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(1), {zeroIndex, numElementsIndex });
    auto sourceStringNumChars = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToSourceStringNumChars);
    auto destinationStringPointerAllocation = functionBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());

    auto destinationStringNumCharsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), destinationStringPointerAllocation, { zeroIndex, numElementsIndex });
    functionBlock->getBuilder()->get()->CreateStore(sourceStringNumChars, destinationStringNumCharsPointer);

    auto destinationStringDepthPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), destinationStringPointerAllocation, { zeroIndex, depthIndex });
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(1), destinationStringDepthPointer);

    auto destinationStringAllocPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), destinationStringPointerAllocation, { zeroIndex, allocIndex });
    auto mallocSize = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocSizeFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocSizeFunction(),
            {
                    sourceStringNumChars,
                    irGenerator->generateIntConstant(charType->getSizeInBytes())
            },
            ""
    );
    auto malloc = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFunction(),
            { mallocSize },
            ""
    );
    functionBlock->getBuilder()->get()->CreateStore(malloc, destinationStringAllocPointer);

    auto sourceAllocation = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(1), { zeroIndex, allocIndex });
    auto charAlignment = DataAlignmentGenerator::generate(charType);
    functionBlock->getBuilder()->get()->CreateMemCpy(malloc, charAlignment, sourceAllocation, charAlignment, mallocSize);
    auto loadedStringCopy = functionBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), destinationStringPointerAllocation);
    functionBlock->getBuilder()->get()->CreateStore(loadedStringCopy, function->getArg(0));
    functionBlock->addVoidReturn();
}