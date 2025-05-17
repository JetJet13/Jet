//
// Created by Johny Georges on 2025-04-16.
//

#include "copy-struct-ir-function.h"

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
    auto pointerType = irGenerator->generateIrPointerType(new IRType(irGenerator->generateCharType()));
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getCopyStructFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto sizeInBytesIndex = irGenerator->generateIntConstant(typeValueType->getSizeInBytesIndex());

    auto numTypes = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), {typeValueType->getNumTypesIndex() });

    auto elementByteOffset = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "elementByteOffset");
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), elementByteOffset);

    auto forLoopIndex = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "forLoopIndex");
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), forLoopIndex);

    // for loop
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
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
    auto typeValueAlloc = forLoopBody->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() });
    auto pointerToTypeValueAtIndex = forLoopBody->CreateInBoundsGEP(typeValueType->getType(), typeValueAlloc, { forLoopIndexValue });
    auto typeValueAtIndex = forLoopBody->CreateLoad(typeValueType->getType(), pointerToTypeValueAtIndex);
    auto structByteOffsetValue = forLoopBody->CreateLoad(intType, elementByteOffset);

    auto destinationPointerAtIndex = forLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), function->getArg(0), { structByteOffsetValue });
    auto sourcePointerAtIndex = forLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), function->getArg(1), { structByteOffsetValue });
    forLoopBody->CreateCall(
            irContext->getIRModule()->getCopyValueFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyValueFunction(),
            { destinationPointerAtIndex, sourcePointerAtIndex, typeValueAtIndex }
    );

    auto sizeInBytesAtIndex = forLoopBody->CreateExtractValue(typeValueAtIndex, { typeValueType->getSizeInBytesIndex() });
    auto newStructByteOffsetValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, structByteOffsetValue, sizeInBytesAtIndex);
    forLoopBody->CreateStore(newStructByteOffsetValue, elementByteOffset);

    auto newForLoopIndexValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    forLoopBody->CreateStore(newForLoopIndexValue, forLoopIndex);
    forLoopBody->CreateBr(forLoopConditionBlock->getBlock());

    // for loop end
    auto functionEndBlock = irGenerator->generateBasicBlock("", irContext);
    forLoopEndBlock->getBuilder()->get()->CreateBr(functionEndBlock->getBlock());

    functionEndBlock->addVoidReturn();
}