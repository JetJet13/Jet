//
// Created by Johny Georges on 2026-05-16.
//

#include "int-add-overflow-ir-function.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"

std::string IntAddOverflowIRFunction::getIntAddOverflowIRFunctionName() {
    return "jet.int.add.overflow";
}

void IntAddOverflowIRFunction::generateIntAddOverflowFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generatePointerType();
    auto raise = irModuleNode->getModule()->get()->getOrInsertFunction("raise", llvm::FunctionType::get(intType, { intType }, false));
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(intType, { intType, intType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           IntAddOverflowIRFunction::getIntAddOverflowIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isOverflowBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(),  "is.overflow");
    auto elseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());

    auto result = functionBlock->getBuilder()->get()->CreateBinaryIntrinsic(
            llvm::Intrinsic::sadd_with_overflow,
            function->getArg(0),
            function->getArg(1)
    );
    auto overflowResult = functionBlock->getBuilder()->get()->CreateExtractValue(result, 1);
    auto isOverflow = functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            overflowResult,
            irGenerator->generateBoolean(true)
    );

    functionBlock->getBuilder()->get()->CreateCondBr(
            isOverflow,
            isOverflowBlock->getBlock(),
            elseBlock->getBlock()
    );
    auto sigTermCode = irGenerator->generateIntConstant(15);
    auto overflowMessage = irGenerator->generateRawString("Error [JET1001]: Int Addition Operation caused overflow \n");
    auto overflowMessageAlloca = isOverflowBlock->getBuilder()->get()->CreateAlloca(overflowMessage->getType());
    isOverflowBlock->getBuilder()->get()->CreateStore(overflowMessage, overflowMessageAlloca);
    isOverflowBlock->getBuilder()->get()->CreateCall(printf, { overflowMessageAlloca });
    isOverflowBlock->getBuilder()->get()->CreateCall(raise, sigTermCode);
    isOverflowBlock->getBuilder()->get()->CreateRet(irGenerator->generateIntConstant(0));

    auto value = elseBlock->getBuilder()->get()->CreateExtractValue(result, 0);
    elseBlock->getBuilder()->get()->CreateRet(value);
}