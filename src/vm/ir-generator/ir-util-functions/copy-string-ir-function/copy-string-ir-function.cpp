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

void CopyStringIRFunction::generateCopyStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = new IRType(irGenerator->generateCharType());
    auto pointerType = irGenerator->generatePointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(charType);

    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType, pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyStringIRFunction::getCopyStringIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto pointerToSourceStringNumChars = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(1), arrayPointerType->getNumElementsIndex());
    auto sourceStringNumChars = InstructionIRInjectorHelper::injectLoad(intType, pointerToSourceStringNumChars, functionBlock);

    auto destinationStringNumCharsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getNumElementsIndex());
    InstructionIRInjectorHelper::injectStore(sourceStringNumChars, destinationStringNumCharsPointer, functionBlock);

    auto destinationStringDepthPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getDepthIndex());
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(1), destinationStringDepthPointer, functionBlock);

    auto sizeInBytes = irGenerator->generateIntConstant(charType->getSizeInBytes());
    auto mallocSize = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocSizeFunction(),
            {
                sourceStringNumChars,
                sizeInBytes
            }
    );
    auto malloc = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFunction(),
            { sourceStringNumChars, sizeInBytes }
    );
    auto destinationStringAllocPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(malloc, destinationStringAllocPointer, functionBlock);

    auto sourceAllocation = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(1), arrayPointerType->getAllocIndex());
    auto loadedSourceAllocation = InstructionIRInjectorHelper::injectLoad(pointerType, sourceAllocation, functionBlock);

    auto charAlignment = charType->getAlignment();
    functionBlock->getBuilder()->get()->CreateMemCpy(malloc, charAlignment, loadedSourceAllocation, charAlignment, mallocSize);

    functionBlock->addVoidReturn();
}