//
// Created by Johny Georges on 2025-05-24.
//

#include "for-in-statement-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-ref-type.h"
#include "../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"

void ForInStatementIRInjectorStrategy::inject(IRForInStatementNode* irForInStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto setupBlock = irForInStatement->getSetupBlock();
    auto forInBlock = irForInStatement->getForInBlock();
    auto bodyBlock = irForInStatement->getBodyBlock();
    auto endBlock = irForInStatement->getEndBlock();

    auto sourceIrType = irForInStatement->getSource()->getIRType()->getSourceType();
    auto zero = setupBlock->getBuilder()->get()->getInt64(0);
    auto one = setupBlock->getBuilder()->get()->getInt64(1);

    // setup
    DebugIRInjectorHelper::injectLog(setupBlock, "START", irInjector, irModule);
    auto arrayPointerType = sourceIrType->isRefType()
            ? (IRArrayPointerType*)((IRRefType*)sourceIrType->getUnderlyingType())
            : (IRArrayPointerType*)sourceIrType;
    auto sourceValue = this->getSourceValue(irForInStatement, arrayPointerType, setupBlock, irInjector, irModule);
    DebugIRInjectorHelper::injectLog(setupBlock, "END", irInjector, irModule);
    auto pointerToSourceArray = setupBlock->getBuilder()->get()->CreateStructGEP(
            arrayPointerType->getType(),
            sourceValue,
            arrayPointerType->getAllocIndex()
    );
    auto pointerToNumElements = setupBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), sourceValue, arrayPointerType->getNumElementsIndex(), "forInNumElemPtr");
    auto indexAllocation = setupBlock->getBuilder()->get()->Insert(irForInStatement->getIndex()->getValue(), "forInIndex");
    setupBlock->getBuilder()->get()->CreateStore(zero, indexAllocation);
    setupBlock->getBuilder()->get()->CreateBr(forInBlock->getBlock());

    // for-in
    auto numElements = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getNumElementsType(), pointerToNumElements, forInBlock);
    auto currentIndex = forInBlock->getBuilder()->get()->CreateLoad(irForInStatement->getIndex()->getAllocatedType(), indexAllocation);
    auto currentIndexLessThanNumElements = forInBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            currentIndex,
            numElements
    );
    forInBlock->getBuilder()->get()->CreateCondBr(currentIndexLessThanNumElements, bodyBlock->getBlock(), irBlock->getLastSuccessorOrSelf()->getBlock());

    // body
    auto sourceArray = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getAllocType(), pointerToSourceArray, bodyBlock);
    auto variableAllocation = bodyBlock->getBuilder()->get()->Insert(irForInStatement->getVariable()->getValue(), "forInVar");
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
    setupBlock->transferNodesToFreeTo(endBlock);
}

llvm::Value* ForInStatementIRInjectorStrategy::getSourceValue(IRForInStatementNode* irForInStatement, IRArrayPointerType* arrayPointerType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule) {
    auto sourceIrType = irForInStatement->getSource()->getIRType()->getSourceType();
    if (sourceIrType->isRefType()) {
        return irInjector->inject(irBlock, irForInStatement->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, irBlock->getScope());
    }

    auto value = irInjector->inject(irBlock, irForInStatement->getSource(), new IROperation(IR_COPY_ASSIGNMENT_OP), irModule, irBlock->getScope());
    auto valueAlloc = irBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType(), nullptr, "VALUE_ALLOC");
    InstructionIRInjectorHelper::injectStore(value, valueAlloc, irBlock, arrayPointerType);
    return valueAlloc;
}