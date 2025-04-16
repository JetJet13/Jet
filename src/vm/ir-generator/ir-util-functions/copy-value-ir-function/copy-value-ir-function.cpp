//
// Created by Johny Georges on 2025-04-16.
//

#include "copy-value-ir-function.h"

std::string CopyValueIRFunction::getCopyValueIRFunctionName() {
    return "jet.copy.value";
}

void CopyValueIRFunction::generateCopyValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyValueIRFunction::getCopyValueIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto literalIfBlock = irGenerator->generateIfBlock(irContext);
    auto literalIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto literalIfElseBlock = irGenerator->generateIfElseBlock(irContext);

    auto pointerIfBlock = irGenerator->generateIfBlock(irContext);
    auto pointerIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto pointerIfElseBlock = irGenerator->generateIfElseBlock(irContext);

    auto structIfBlock = irGenerator->generateIfBlock(irContext);
    auto structIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto structIfElseBlock = irGenerator->generateIfElseBlock(irContext);

    auto arrayIfBlock = irGenerator->generateIfBlock(irContext);
    auto arrayIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto arrayIfElseBlock = irGenerator->generateIfElseBlock(irContext);

//    auto functionLoopEndBlock = irGenerator->generateBasicBlock("", irContext);
//    auto isDepthOne = functionBlock->getBuilder()->get()->CreateICmp(
//            llvm::CmpInst::Predicate::ICMP_EQ,
//            sourceArrayDepth,
//            irGenerator->generateIntConstant(1)
//    );
//    functionBlock->getBuilder()->get()->CreateCondBr(isDepthOne, depthOneBlock->getBlock(), functionLoopPrepBlock->getBlock());


    functionBlock->addVoidReturn();
}