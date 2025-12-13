//
// Created by Johny Georges on 2025-04-30.
//

#include "free-struct-ir-function.h"
#include "../../../types/ir-type-id.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

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
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getFreeStructFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    // for loop blocks
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto isValueNotFreeableThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto isValueNotFreeableElseBlock = irGenerator->generateIfElseBlock(irContext);
    auto isValueNotFreeableEndBlock = irGenerator->generateIfElseBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);

    auto numTypes = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getNumTypesIndex() }, "numTypes");
    auto typeValueAlloc = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getAllocIndex() }, "typeValueAlloc");
    auto elementByteOffset = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "elementByteOffset");
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), elementByteOffset, functionBlock);

    auto forLoopIndex = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "forLoopIndex");
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndex, functionBlock);
    functionBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());
    // for loop condition
    auto forLoopIndexValue = forLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, forLoopIndex);
    auto pointerToTypeValueAtIndex = forLoopConditionBlock->getBuilder()->get()->CreateInBoundsGEP(pointerType, typeValueAlloc, { forLoopIndexValue });
    auto typeValuePointerAtIndex = InstructionIRInjectorHelper::injectLoad(pointerType, pointerToTypeValueAtIndex, forLoopConditionBlock);
    auto typeValueAtIndex = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), typeValuePointerAtIndex, forLoopConditionBlock, typeValueType);
    auto isForLoopIndexLessThanNumElements = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            numTypes
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(isForLoopIndexLessThanNumElements, forLoopBodyBlock->getBlock(), forLoopEndBlock->getBlock());

    // for loop body
    auto forLoopBody = forLoopBodyBlock->getBuilder()->get();
    auto typeValueIdAtIndex = forLoopBody->CreateExtractValue(typeValueAtIndex, typeValueType->getIdIndex());
    auto structByteOffsetValue = forLoopBody->CreateLoad(intType, elementByteOffset);

    auto pointerAtIndex = forLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), function->getArg(0), { structByteOffsetValue });
    auto isValueTypeLiteral = forLoopBody->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.LITERAL),
            "isValueTypeLiteral"
    );

    forLoopBody->CreateCondBr(isValueTypeLiteral, isValueNotFreeableThenBlock->getBlock(), isValueNotFreeableElseBlock->getBlock());
    isValueNotFreeableThenBlock->getBuilder()->get()->CreateBr(isValueNotFreeableEndBlock->getBlock());
    isValueNotFreeableElseBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeValueFunction(),
            { pointerAtIndex, typeValueAtIndex }
    );
    isValueNotFreeableElseBlock->getBuilder()->get()->CreateBr(isValueNotFreeableEndBlock->getBlock());

    auto sizeInBytesAtIndex = isValueNotFreeableEndBlock->getBuilder()->get()->CreateExtractValue(typeValueAtIndex, typeValueType->getSizeInBytesIndex());
    auto newStructByteOffsetValue = isValueNotFreeableEndBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, structByteOffsetValue, sizeInBytesAtIndex);
    InstructionIRInjectorHelper::injectStore(newStructByteOffsetValue, elementByteOffset, isValueNotFreeableEndBlock);
    auto newForLoopIndexValue = isValueNotFreeableEndBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    isValueNotFreeableEndBlock->getBuilder()->get()->CreateStore(newForLoopIndexValue, forLoopIndex);
    isValueNotFreeableEndBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());


    // for loop end
    auto functionEndBlock = irGenerator->generateBasicBlock("", irContext);
    forLoopEndBlock->getBuilder()->get()->CreateBr(functionEndBlock->getBlock());

    functionEndBlock->addVoidReturn();
}