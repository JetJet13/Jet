//
// Created by Johny Georges on 2025-04-30.
//

#include "free-struct-ir-function.h"
#include "../../../types/ir-type-id.h"

std::string FreeStructIRFunction::getFreeStructIRFunctionName() {
    return "jet.free.struct";
}

void FreeStructIRFunction::declareFreeStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeStructIRFunction::getFreeStructIRFunctionName(), irModuleNode->getModule());
}

void FreeStructIRFunction::generateFreeStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType(new IRType(irGenerator->generateCharType()));
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getFreeStructFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto sizeInBytesIndex = irGenerator->generateIntConstant(typeValueType->getSizeInBytesIndex());
    auto numTypesIndex = irGenerator->generateIntConstant(typeValueType->getNumTypesIndex());
    auto allocIndex = irGenerator->generateIntConstant(typeValueType->getAllocIndex());
    auto typeValueIdIndex = irGenerator->generateIntConstant(typeValueType->getIdIndex());

    auto numTypes = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getNumTypesIndex() });

    auto elementByteOffset = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "elementByteOffset");
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), elementByteOffset);

    auto forLoopIndex = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "forLoopIndex");
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), forLoopIndex);

    // for loop
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto isValueNotFreeableThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto isValueNotFreeableElseBlock = irGenerator->generateIfElseBlock(irContext);
    auto isValueNotFreeableEndBlock = irGenerator->generateIfElseBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);
    functionBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());
    // for loop condition
    auto forLoopIndexValue = forLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, forLoopIndex);
    auto isForLoopIndexLessThanNumElements = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            numTypes
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(isForLoopIndexLessThanNumElements, forLoopBodyBlock->getBlock(), forLoopEndBlock->getBlock());

    // for loop body
    auto forLoopBody = forLoopBodyBlock->getBuilder()->get();
    auto typeValueAtIndex = forLoopBody->CreateExtractValue(function->getArg(1), { typeValueType->getAllocIndex() });
    auto pointerToTypeValueIdAtIndex = forLoopBody->CreateInBoundsGEP(typeValueType->getType(), typeValueAtIndex, { zeroIndex, typeValueIdIndex });
    auto typeValueIdAtIndex = forLoopBody->CreateLoad(intType, pointerToTypeValueIdAtIndex, "valueTypeIdAtIndex");
    auto structByteOffsetValue = forLoopBody->CreateLoad(intType, elementByteOffset);

    auto pointerAtIndex = forLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), function->getArg(0), {structByteOffsetValue });
    auto isValueTypeLiteral = forLoopBody->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.LITERAL),
            "isValueTypeLiteral"
    );

    forLoopBody->CreateCondBr(isValueTypeLiteral, isValueNotFreeableThenBlock->getBlock(), isValueNotFreeableElseBlock->getBlock());
    isValueNotFreeableThenBlock->getBuilder()->get()->CreateBr(isValueNotFreeableEndBlock->getBlock());
    auto loadedTypeValueAtIndex = isValueNotFreeableElseBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), typeValueAtIndex);
    isValueNotFreeableElseBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeValueFunction()->getFunctionType(),
            irContext->getIRModule()->getFreeValueFunction(),
            { pointerAtIndex, loadedTypeValueAtIndex }
    );
    isValueNotFreeableElseBlock->getBuilder()->get()->CreateBr(isValueNotFreeableEndBlock->getBlock());

    auto sizeInBytesAtIndexPointer = isValueNotFreeableEndBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), typeValueAtIndex, { zeroIndex, sizeInBytesIndex });
    auto loadedSizeInBytesAtIndex = isValueNotFreeableEndBlock->getBuilder()->get()->CreateLoad(intType, sizeInBytesAtIndexPointer);
    auto newStructByteOffsetValue = isValueNotFreeableEndBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, structByteOffsetValue, loadedSizeInBytesAtIndex);
    isValueNotFreeableEndBlock->getBuilder()->get()->CreateStore(newStructByteOffsetValue, elementByteOffset);

    auto newForLoopIndexValue = isValueNotFreeableEndBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    isValueNotFreeableEndBlock->getBuilder()->get()->CreateStore(newForLoopIndexValue, forLoopIndex);
    isValueNotFreeableEndBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    // for loop end
    auto functionEndBlock = irGenerator->generateBasicBlock("", irContext);
    forLoopEndBlock->getBuilder()->get()->CreateBr(functionEndBlock->getBlock());

    functionEndBlock->addVoidReturn();
}