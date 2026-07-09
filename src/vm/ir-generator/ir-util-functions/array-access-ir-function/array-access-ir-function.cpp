//
// Created by Johny Georges on 2024-09-23.
//

#include "array-access-ir-function.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string ArrayAccessIRFunction::getArrayAccessIRFunctionName() {
    return "jet.array.access.check";
}

void ArrayAccessIRFunction::generateArrayAccessFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generatePointerType();
    auto voidType = irGenerator->generateVoidType()->getType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto raise = irModuleNode->getModule()->get()->getOrInsertFunction("raise", llvm::FunctionType::get(intType, { intType }, false));
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType, { pointerType, intType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, ArrayAccessIRFunction::getArrayAccessIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto zero = irGenerator->generateIntConstant(0);

    auto pointerToNumElements = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getNumElementsIndex());
    auto loadedNumElements = InstructionIRInjectorHelper::injectLoad(intType, pointerToNumElements, functionBlock);
    auto isIndexGreaterThanOrEqualToNumElements = functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGE,
            function->getArg(1),
            loadedNumElements
    );
    auto isIndexLessThanZero = functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            function->getArg(1),
            zero
    );
    auto isIndexNotInRange = functionBlock->getBuilder()->get()->CreateBinOp(
        llvm::Instruction::BinaryOps::Or,
        isIndexGreaterThanOrEqualToNumElements,
        isIndexLessThanZero
    );
    auto notInRangeBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(),  "not.ok.");
    auto inRangeBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope(), "ok.");
    functionBlock->getBuilder()->get()->CreateCondBr(
        isIndexNotInRange,
        notInRangeBlock->getBlock(),
        inRangeBlock->getBlock()
    );
    auto outOfBoundsMessage = irGenerator->generateRawString("Error [JET2001]: Array Access Out Of Bounds \n");
    auto outOfBoundsMessageAlloca = notInRangeBlock->getBuilder()->get()->CreateAlloca(outOfBoundsMessage->getType());
    notInRangeBlock->getBuilder()->get()->CreateStore(outOfBoundsMessage, outOfBoundsMessageAlloca);
    notInRangeBlock->getBuilder()->get()->CreateCall(printf, { outOfBoundsMessageAlloca });
    auto sigTermCode = irGenerator->generateIntConstant(15);
    notInRangeBlock->getBuilder()->get()->CreateCall(raise, sigTermCode);
    notInRangeBlock->addVoidReturn();
    inRangeBlock->addVoidReturn();
}