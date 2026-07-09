//
// Created by Johny Georges on 2025-05-01.
//

#include "free-array-ir-function.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../types/ir-type-id.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string FreeArrayIRFunction::getFreeArrayIRFunctionName() {
    return "jet.free.array";
}

void FreeArrayIRFunction::declareFreeArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeArrayIRFunction::getFreeArrayIRFunctionName(), irModuleNode->getModule()->get());
}

void FreeArrayIRFunction::generateFreeArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generatePointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto numElementsIndex = arrayPointerType->getNumElementsIndex();
    auto allocIndex = arrayPointerType->getAllocIndex();

    auto function = irModuleNode->getFreeArrayFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isElementTypeLiteralIfBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isElementTypeLiteralThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->createChild();
    auto forLoopPrepBlock = functionBlock->getLastChildOrSelf();
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext, functionBlock->getScope());
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext, functionBlock->getScope());
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext, functionBlock->getScope());

    auto pointerToSourceArrayNumElements = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), numElementsIndex);
    auto sourceArrayNumElements = InstructionIRInjectorHelper::injectLoad(intType, pointerToSourceArrayNumElements, functionBlock);

    auto pointerToSourceArrayMalloc = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), allocIndex);
    auto sourceArrayMalloc = InstructionIRInjectorHelper::injectLoad(pointerType, pointerToSourceArrayMalloc, functionBlock);

    auto elementTypeValuePointer = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getAllocIndex() }, "elementTypeValue");
    auto elementTypeValue = functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), elementTypeValuePointer);
    auto elementTypeValueId = functionBlock->getBuilder()->get()->CreateExtractValue(elementTypeValue, { typeValueType->getIdIndex() }, "elementTypeValueId");

    functionBlock->getBuilder()->get()->CreateBr(isElementTypeLiteralIfBlock->getBlock());

    auto isElementTypeLiteral = isElementTypeLiteralIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            elementTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.LITERAL)
    );
    isElementTypeLiteralIfBlock->getBuilder()->get()->CreateCondBr(isElementTypeLiteral, isElementTypeLiteralThenBlock->getBlock(), forLoopPrepBlock->getBlock());

    isElementTypeLiteralThenBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getMallocFreeFunction(),
        { sourceArrayMalloc }
    );
    isElementTypeLiteralThenBlock->addVoidReturn();

    // for loop prep block
    auto elementSizeInBytes = forLoopPrepBlock->getBuilder()->get()->CreateExtractValue(elementTypeValue, { typeValueType->getSizeInBytesIndex() }, "elementTypeSizeInBytes");
    auto elementByteOffset = forLoopPrepBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "elementByteOffset");
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), elementByteOffset, forLoopPrepBlock);
    auto forLoopIndex = forLoopPrepBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "forLoopIndex");
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndex, forLoopPrepBlock);
    forLoopPrepBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    // for loop condition
    auto elementByteOffsetValue = InstructionIRInjectorHelper::injectLoad(intType, elementByteOffset, forLoopConditionBlock);
    auto forLoopIndexValue = InstructionIRInjectorHelper::injectLoad(intType, forLoopIndex, forLoopConditionBlock);
    auto forLoopIndexLessThanNumElements = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            sourceArrayNumElements
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(forLoopIndexLessThanNumElements, forLoopBodyBlock->getBlock(), forLoopEndBlock->getBlock());

    // for loop body
    auto forLoopBody = forLoopBodyBlock->getBuilder()->get();

    auto pointerToElementAtIndex = forLoopBody->CreateInBoundsGEP(pointerIntType, sourceArrayMalloc, { elementByteOffsetValue });
    forLoopBody->CreateCall(
        irContext->getIRModule()->getFreeValueFunction(),
        { pointerToElementAtIndex, elementTypeValue }
    );

    auto newElementByteOffsetValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, elementByteOffsetValue, elementSizeInBytes);
    InstructionIRInjectorHelper::injectStore(newElementByteOffsetValue, elementByteOffset, forLoopBodyBlock);

    auto newForLoopIndexValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    InstructionIRInjectorHelper::injectStore(newForLoopIndexValue, forLoopIndex, forLoopBodyBlock);
    forLoopBody->CreateBr(forLoopConditionBlock->getBlock());

    // for loop end
    forLoopEndBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFreeFunction(),
            { sourceArrayMalloc }
    );
    forLoopEndBlock->addVoidReturn();
}