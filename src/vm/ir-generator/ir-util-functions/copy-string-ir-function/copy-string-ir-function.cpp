//
// Created by Johny Georges on 2024-09-26.
//

#include "copy-string-ir-function.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string CopyStringIRFunction::getCopyStringIRFunctionName() {
    return "jet.copy.string";
}

void CopyStringIRFunction::generateCopyStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = new IRType(irGenerator->generateCharType());
    auto pointerType = irGenerator->generatePointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(charType);
    auto zeroIndex = irGenerator->generateIntConstant(0);

    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());

    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType, pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyStringIRFunction::getCopyStringIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto pointerToSourceStringNumChars = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(1), arrayPointerType->getNumElementsIndex());
    auto sourceStringNumChars = InstructionIRInjectorHelper::injectLoad(intType, pointerToSourceStringNumChars, functionBlock);
    //    auto sourceStringNumChars = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToSourceStringNumChars);
    auto destinationStringPointerAllocation = functionBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());

    auto destinationStringNumCharsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), destinationStringPointerAllocation, arrayPointerType->getNumElementsIndex());
    InstructionIRInjectorHelper::injectStore(sourceStringNumChars, destinationStringNumCharsPointer, functionBlock);
//    functionBlock->getBuilder()->get()->CreateStore(sourceStringNumChars, destinationStringNumCharsPointer);

    auto destinationStringDepthPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), destinationStringPointerAllocation, arrayPointerType->getDepthIndex());
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(1), destinationStringDepthPointer, functionBlock);
    //    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(1), destinationStringDepthPointer);

    auto destinationStringAllocPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), destinationStringPointerAllocation, arrayPointerType->getAllocIndex());
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
    InstructionIRInjectorHelper::injectStore(malloc, destinationStringAllocPointer, functionBlock);
//    functionBlock->getBuilder()->get()->CreateStore(malloc, destinationStringAllocPointer);

    auto sourceAllocation = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(1), arrayPointerType->getAllocIndex());
    auto loadedSourceAllocation = InstructionIRInjectorHelper::injectLoad(pointerType, sourceAllocation, functionBlock);
//    auto loadedSourceAllocation = functionBlock->getBuilder()->get()->CreateLoad(pointerType, sourceAllocation);
    auto charAlignment = charType->getAlignment();
    functionBlock->getBuilder()->get()->CreateMemCpy(malloc, charAlignment, loadedSourceAllocation, charAlignment, mallocSize);
    auto loadedStringCopy = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), destinationStringPointerAllocation, functionBlock, arrayPointerType);
//    auto loadedStringCopy = functionBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), destinationStringPointerAllocation);
    InstructionIRInjectorHelper::injectStore(loadedStringCopy, function->getArg(0), functionBlock);
//    functionBlock->getBuilder()->get()->CreateStore(loadedStringCopy, function->getArg(0));
    functionBlock->addVoidReturn();
}