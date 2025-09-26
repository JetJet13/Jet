//
// Created by Johny Georges on 2025-05-24.
//

#include "for-in-statement-ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"

void ForInStatementIRInjectorStrategy::inject(IRForInStatementNode* irForInStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto setupBlock = irForInStatement->getSetupBlock();
    auto forInBlock = irForInStatement->getForInBlock();
    auto bodyBlock = irForInStatement->getBodyBlock();
    auto endBlock = irForInStatement->getEndBlock();

    auto arrayPointerType = (IRArrayPointerType*)irForInStatement->getSource()->getIRType()->getSourceType();
    auto zero = setupBlock->getBuilder()->get()->getInt64(0);
    auto one = setupBlock->getBuilder()->get()->getInt64(1);
    auto numElementsIndex = setupBlock->getBuilder()->get()->getInt64(arrayPointerType->getNumElementsIndex());
    auto allocIndex = setupBlock->getBuilder()->get()->getInt64(arrayPointerType->getAllocIndex());
    // setup
    auto sourceValue = irInjector->inject(setupBlock, irForInStatement->getSource(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    auto numElementsPointer = setupBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceValue, { zero, numElementsIndex }, "forInNumElemPtr");
    auto pointerToSourceArray = setupBlock->getBuilder()->get()->CreateInBoundsGEP(
            arrayPointerType->getType(),
            sourceValue,
            { zero, allocIndex }
    );
    auto sourceArray = setupBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), pointerToSourceArray, "sourceArray");
    auto indexAllocation = setupBlock->getBuilder()->get()->Insert(irForInStatement->getIndex()->getValue(), "forInIndex");
    setupBlock->getBuilder()->get()->CreateStore(zero, indexAllocation);
    auto variableAllocation = setupBlock->getBuilder()->get()->Insert(irForInStatement->getVariable()->getValue(), "forInVar");
    setupBlock->getBuilder()->get()->CreateBr(forInBlock->getBlock());

    // for-in
    auto numElements = forInBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getNumElementsType(), numElementsPointer);
    auto currentIndex = forInBlock->getBuilder()->get()->CreateLoad(irForInStatement->getIndex()->getAllocatedType(), indexAllocation);
    auto currentIndexLessThanNumElements = forInBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            currentIndex,
            numElements
    );
    forInBlock->getBuilder()->get()->CreateCondBr(currentIndexLessThanNumElements, bodyBlock->getBlock(), endBlock->getBlock());

    // body
    auto pointerToNewVariableValue = bodyBlock->getBuilder()->get()->CreateInBoundsGEP(
        arrayPointerType->getElementType(),
        sourceArray,
        { currentIndex }
    );
    auto loadedNewVariableValue = bodyBlock->getBuilder()->get()->CreateLoad(
        irForInStatement->getVariable()->getAllocatedType(),
        pointerToNewVariableValue
    );
    bodyBlock->getBuilder()->get()->CreateStore(loadedNewVariableValue, variableAllocation);
    irInjector->inject(irBlock, bodyBlock, irModule, scope);
    auto newIndexValue = bodyBlock->getLastSuccessorOrSelf()->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, currentIndex, one);
    bodyBlock->getLastSuccessorOrSelf()->getBuilder()->get()->CreateStore(newIndexValue, indexAllocation);
    bodyBlock->getLastSuccessorOrSelf()->getBuilder()->get()->CreateBr(forInBlock->getBlock());
}