//
// Created by Johny Georges on 2025-04-16.
//

#include "copy-struct-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string CopyStructIRFunction::getCopyStructIRFunctionName() {
    return "jet.copy.struct";
}

void CopyStructIRFunction::declareCopyStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyStructIRFunction::getCopyStructIRFunctionName(), irModuleNode->getModule());
}

void CopyStructIRFunction::generateCopyStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getCopyStructFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto numTypes = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getNumTypesIndex() });
//    functionBlock->getBuilder()->get()->CreateCall(irModuleNode->getPrintDebugMarkerFunction(), { numTypes });
//    functionBlock->getBuilder()->get()->CreateCall(irModuleNode->getPrintNewLineFunction(),{});
    auto elementByteOffset = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "elementByteOffset");
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), elementByteOffset, functionBlock);
//    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), elementByteOffset);

    auto forLoopIndex = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "forLoopIndex");
    auto typeValueAlloc = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() }, "typeValueAlloc");
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndex, functionBlock);
//    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), forLoopIndex);

    // for loop
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);
    functionBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());
    // for loop condition
    auto structByteOffsetValue = InstructionIRInjectorHelper::injectLoad(intType, elementByteOffset, forLoopConditionBlock);
//    auto structByteOffsetValue = forLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, elementByteOffset);
    auto forLoopIndexValue = InstructionIRInjectorHelper::injectLoad(intType, forLoopIndex, forLoopConditionBlock);
//    auto forLoopIndexValue = forLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, forLoopIndex);
    auto pointerToTypeValueAtIndex = forLoopConditionBlock->getBuilder()->get()->CreateInBoundsGEP(pointerType, typeValueAlloc, { forLoopIndexValue });
//    auto typeValuePointerAtIndex = forLoopConditionBlock->getBuilder()->get()->CreateLoad(pointerType, pointerToTypeValueAtIndex);
    auto typeValuePointerAtIndex = InstructionIRInjectorHelper::injectLoad(pointerType, pointerToTypeValueAtIndex, forLoopConditionBlock);
//    auto typeValueAtIndex = forLoopConditionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), typeValuePointerAtIndex);
    auto typeValueAtIndex = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), typeValuePointerAtIndex, forLoopConditionBlock, typeValueType);
    auto isForLoopIndexLessThanNumElements = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            numTypes
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(isForLoopIndexLessThanNumElements, forLoopBodyBlock->getBlock(), forLoopEndBlock->getBlock());

    // for loop body
    auto forLoopBody = forLoopBodyBlock->getBuilder()->get();
    auto destinationPointerAtIndex = forLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), function->getArg(0), { structByteOffsetValue });
    auto sourcePointerAtIndex = forLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), function->getArg(1), { structByteOffsetValue });
    forLoopBody->CreateCall(
            irContext->getIRModule()->getCopyValueFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyValueFunction(),
            { destinationPointerAtIndex, sourcePointerAtIndex, typeValueAtIndex }
    );

    auto sizeInBytesAtIndex = forLoopBody->CreateExtractValue(typeValueAtIndex, { typeValueType->getSizeInBytesIndex() });
    forLoopBody->CreateCall(irModuleNode->getPrintDebugMarkerFunction(), { sizeInBytesAtIndex });
    forLoopBody->CreateCall(irModuleNode->getPrintNewLineFunction(),{});
    auto newStructByteOffsetValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, structByteOffsetValue, sizeInBytesAtIndex);
    InstructionIRInjectorHelper::injectStore(newStructByteOffsetValue, elementByteOffset, forLoopBodyBlock);
//    forLoopBody->CreateStore(newStructByteOffsetValue, elementByteOffset);

    auto newForLoopIndexValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    InstructionIRInjectorHelper::injectStore(newForLoopIndexValue, forLoopIndex, forLoopBodyBlock);
//    forLoopBody->CreateStore(newForLoopIndexValue, forLoopIndex);
    forLoopBody->CreateBr(forLoopConditionBlock->getBlock());

    // for loop end
    auto functionEndBlock = irGenerator->generateBasicBlock("", irContext);
    forLoopEndBlock->getBuilder()->get()->CreateCall(irModuleNode->getPrintNewLineFunction(),{});
    forLoopEndBlock->getBuilder()->get()->CreateBr(functionEndBlock->getBlock());
    functionEndBlock->addVoidReturn();
}