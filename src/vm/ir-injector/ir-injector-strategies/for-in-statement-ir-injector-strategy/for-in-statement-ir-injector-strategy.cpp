//
// Created by Johny Georges on 2025-05-24.
//

#include "for-in-statement-ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ForInStatementIRInjectorStrategy::inject(IRForInStatementNode* irForInStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto setupBlock = irForInStatement->getSetupBlock();
    auto forInBlock = irForInStatement->getForInBlock();
    auto bodyBlock = irForInStatement->getBodyBlock();

    auto arrayPointerType = (IRArrayPointerType*)irForInStatement->getSource()->getIRType()->getSourceType();
    auto zero = setupBlock->getBuilder()->get()->getInt64(0);
    auto one = setupBlock->getBuilder()->get()->getInt64(1);
    auto numElementsIndex = arrayPointerType->getNumElementsIndex();
    auto allocIndex = arrayPointerType->getAllocIndex();
    // setup
    auto sourceValue = irInjector->inject(setupBlock, irForInStatement->getSource(), new IROperation(IR_OPERAND_POINTER_OP), irModule, setupBlock->getScope());
    auto numElementsPointer = setupBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), sourceValue, numElementsIndex, "forInNumElemPtr");
    auto numElements = setupBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getNumElementsType(), numElementsPointer);
    auto pointerToSourceArray = setupBlock->getBuilder()->get()->CreateStructGEP(
            arrayPointerType->getType(),
            sourceValue,
            allocIndex
    );
    auto sourceArray = setupBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), pointerToSourceArray, "sourceArray");
    auto indexAllocation = setupBlock->getBuilder()->get()->Insert(irForInStatement->getIndex()->getValue(), "forInIndex");
    setupBlock->getBuilder()->get()->CreateStore(zero, indexAllocation);
    auto variableAllocation = setupBlock->getBuilder()->get()->Insert(irForInStatement->getVariable()->getValue(), "forInVar");
    setupBlock->getBuilder()->get()->CreateBr(forInBlock->getBlock());

    // for-in
    auto currentIndex = forInBlock->getBuilder()->get()->CreateLoad(irForInStatement->getIndex()->getAllocatedType(), indexAllocation);
    auto currentIndexLessThanNumElements = forInBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            currentIndex,
            numElements
    );
    forInBlock->getBuilder()->get()->CreateCondBr(currentIndexLessThanNumElements, bodyBlock->getBlock(), irBlock->getLastSuccessorOrSelf()->getBlock());

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
    auto capturedVariable = irForInStatement->getCapturedVariable();
    if (capturedVariable) {
        auto capturedVariableAlloc = InstructionIRInjectorHelper::inject(capturedVariable.value()->getVariable(), bodyBlock);
        InstructionIRInjectorHelper::injectStore(loadedNewVariableValue, capturedVariableAlloc, bodyBlock);
        InstructionIRInjectorHelper::inject(capturedVariable.value()->getArc(), bodyBlock);
    } else {
        InstructionIRInjectorHelper::injectStore(loadedNewVariableValue, variableAllocation, bodyBlock);
    }
    irInjector->inject(irBlock, bodyBlock, irModule);
    auto lastBodyBlock = bodyBlock->getLastSuccessorOrSelf();
    if (lastBodyBlock->hasBranchInstruction()) {
        lastBodyBlock->removeLastInstruction();
    }
    auto newIndexValue = lastBodyBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, currentIndex, one);
    lastBodyBlock->getBuilder()->get()->CreateStore(newIndexValue, indexAllocation);
    lastBodyBlock->getBuilder()->get()->CreateBr(forInBlock->getBlock());
}