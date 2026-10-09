// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2025-05-24.
//

#include "for-in-statement-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-shared-ptr-type.h"
#include "../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"

void ForInStatementIRInjectorStrategy::inject(std::shared_ptr<IRForInStatementNode> irForInStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    irBlock->getLastChildOrSelf()->getBuilder()->get()->CreateBr(irForInStatement->getSetupBlock()->getBlock());

    auto setupBlock = irForInStatement->getSetupBlock();
    auto forInBlock = irForInStatement->getForInBlock();
    auto bodyBlock = irForInStatement->getBodyBlock();
    auto endBlock = irForInStatement->getEndBlock();

    auto sourceIrType = irForInStatement->getSource()->getIRType()->getSourceType();
    auto zero = setupBlock->getBuilder()->get()->getInt64(0);
    auto one = setupBlock->getBuilder()->get()->getInt64(1);

    // setup
    DebugIRInjectorHelper::injectLog(setupBlock, "START", irInjector, irModule);
    auto arrayPointerType = sourceIrType->isSharedType()
            ? std::dynamic_pointer_cast<IRArrayPointerType>(std::dynamic_pointer_cast<IRSharedPtrType>(sourceIrType)->getUnderlyingType())
            : std::dynamic_pointer_cast<IRArrayPointerType>(sourceIrType);
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
    forInBlock->getBuilder()->get()->CreateCondBr(currentIndexLessThanNumElements, bodyBlock->getBlock(), endBlock->getBlock());

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

    auto lastBodyBlock = bodyBlock->getLastChildOrSelf();
    endBlock->getBlock()->moveAfter(lastBodyBlock->getBlock());

    setupBlock->setFinalBlockForNodesToFree(endBlock);
    setupBlock->preventFreeingNodes();
    FreeIRInjectorHelper::freeForInLoopSource(endBlock, setupBlock, irInjector, irModule, scope);
    irBlock->adoptNodesToFreeFrom(setupBlock);

    if (lastBodyBlock->hasReturnInstruction()) {
        this->finalize(irForInStatement, irBlock);
        return;
    }

    if (lastBodyBlock->hasBranchInstruction()) {
        lastBodyBlock->removeLastInstruction();
    }

    auto newIndexValue = lastBodyBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, currentIndex, one);
    lastBodyBlock->getBuilder()->get()->CreateStore(newIndexValue, indexAllocation);
    lastBodyBlock->getBuilder()->get()->CreateBr(forInBlock->getBlock());

    this->finalize(irForInStatement, irBlock);
}

llvm::Value* ForInStatementIRInjectorStrategy::getSourceValue(std::shared_ptr<IRForInStatementNode> irForInStatement, std::shared_ptr<IRArrayPointerType> arrayPointerType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    auto sourceIrType = irForInStatement->getSource()->getIRType()->getSourceType();
    if (sourceIrType->isSharedType()) {
        return irInjector->inject(irBlock, irForInStatement->getSource(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, irBlock->getScope());
    }

    return irInjector->inject(irBlock, irForInStatement->getSource(), std::make_shared<IROperation>(IR_OPERAND_POINTER_OP), irModule, irBlock->getScope());
}

void ForInStatementIRInjectorStrategy::finalize(std::shared_ptr<IRForInStatementNode> irForInStatement, std::shared_ptr<IRBlockNode> irBlock) {
    auto parentBlock = irBlock->getParentBlock().value_or(irBlock);
    irForInStatement->nestIn(parentBlock);
    parentBlock->createChild();
    irForInStatement->getEndBlock()->getBuilder()->get()->CreateBr(
            parentBlock->getLastChildOrSelf()->getBlock()
    );
    parentBlock->getLastChildOrSelf()->getBlock()->moveAfter(irForInStatement->getEndBlock()->getBlock());
}