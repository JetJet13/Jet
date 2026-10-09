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
// Created by Johny Georges on 2025-03-07.
//

#include "literal-ir-binary-arithmetic-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../../shared/utils/logger/logger.h"
#include "../../../../../utils/binary-arithmetic-dsu/binary-arithmetic-dsu.h"

llvm::Value* LiteralIRBinaryArithmeticExpressionInjectorStrategy::inject(std::shared_ptr<IRBinaryArithmeticExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irOperations = irExpression->getListOfOperations();

    auto irOperands = irExpression->getListOfOperands();
    auto irOperandValues = std::vector<std::shared_ptr<BinaryArithmeticDSU>>();
    for (auto irOperand : irOperands) {
        auto irValue = irInjector->inject(irBlock, irOperand, (std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))->markAsUnderlying(), irModule, scope);
        irOperandValues.push_back(std::make_shared<BinaryArithmeticDSU>(irValue));
    }

    for (int i = 0; i < irOperations.size(); ++i) {
        auto op = this->findNextOperationIndex(&irOperations);
        auto leftValue = irOperandValues.at(op->getLeftOperandIndex());
        auto rightValue = irOperandValues.at(op->getRightOperandIndex());
        auto result = this->calculate(irBlock, op, leftValue->getValue(), rightValue->getValue(), irModule);
        auto resultDSU = std::make_shared<BinaryArithmeticDSU>(result);
        leftValue->merge(rightValue);
        resultDSU->merge(leftValue);
    }

    auto finalResult = irOperandValues.at(irOperandValues.size() - 1)->getValue();
    if (irOperation->isOperandPointer()) {
        auto allocation = irBlock->getBuilder()->get()->CreateAlloca(finalResult->getType());
        InstructionIRInjectorHelper::injectStore(finalResult, allocation, irBlock);
        return allocation;
    }
    return finalResult;
}

std::shared_ptr<IRBinaryArithmeticNode> LiteralIRBinaryArithmeticExpressionInjectorStrategy::findNextOperationIndex(std::vector<std::shared_ptr<IRBinaryOperatorNode>>* operations) {
    for (int i = 0; i < operations->size(); ++i) {
        auto currentOp = operations->at(i);
        if (currentOp->isHandled()) continue;

        for (int j = i + 1; j < operations->size(); ++j) {
            auto otherOp = operations->at(j);
            if (!otherOp->isHandled() && otherOp->isHigherPriorityThan(currentOp)) {
                otherOp->markAsHandled();
                return std::make_shared<IRBinaryArithmeticNode>(otherOp->getOp(), j, j+1);
            }
        }
        currentOp->markAsHandled();
        return std::make_shared<IRBinaryArithmeticNode>(currentOp->getOp(), i, i+1);
    }
    throw std::logic_error("unable to find next binary arithmetic operation");
}

llvm::Value* LiteralIRBinaryArithmeticExpressionInjectorStrategy::calculate(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRBinaryArithmeticNode> binaryOp, llvm::Value* leftValue, llvm::Value* rightValue, std::shared_ptr<IRModuleNode> irModule) {
    if (binaryOp->isIntAddition()) {
        return irBlock->getBuilder()->get()->CreateCall(
            irModule.get()->getIntAddOverflowFunction(),
            { leftValue, rightValue }
        );
    } else if (binaryOp->isIntSubtraction()) {
        return irBlock->getBuilder()->get()->CreateCall(
                irModule.get()->getIntSubOverflowFunction(),
                { leftValue, rightValue }
        );
    } else if (binaryOp->isIntMultiplication()) {
        return irBlock->getBuilder()->get()->CreateCall(
                irModule.get()->getIntMultiplyOverflowFunction(),
                { leftValue, rightValue }
        );
    }
    return irBlock->getBuilder()->get()->CreateBinOp(binaryOp->getOp()->getOpcode(), leftValue, rightValue);
}