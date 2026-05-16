//
// Created by Johny Georges on 2025-03-07.
//

#include "literal-ir-binary-arithmetic-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../../shared/utils/logger/logger.h"
#include "../../../../../utils/binary-arithmetic-dsu/binary-arithmetic-dsu.h"

llvm::Value* LiteralIRBinaryArithmeticExpressionInjectorStrategy::inject(IRBinaryArithmeticExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irOperations = irExpression->getListOfOperations();

    auto irOperands = irExpression->getListOfOperands();
    auto irOperandValues = std::vector<BinaryArithmeticDSU*>();
    for (auto irOperand : irOperands) {
        auto irValue = irInjector->inject(irBlock, irOperand, (new IROperation(IR_OPERAND_VALUE_OP))->markAsUnderlying(), irModule, scope);
        irOperandValues.push_back(new BinaryArithmeticDSU(irValue));
    }

    for (int i = 0; i < irOperations.size(); ++i) {
        auto op = this->findNextOperationIndex(&irOperations);
        auto leftValue = irOperandValues.at(op->getLeftOperandIndex());
        auto rightValue = irOperandValues.at(op->getRightOperandIndex());
        auto result = this->calculate(irBlock, op, leftValue->getValue(), rightValue->getValue(), irModule);
        auto resultDSU = new BinaryArithmeticDSU(result);
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

IRBinaryArithmeticNode* LiteralIRBinaryArithmeticExpressionInjectorStrategy::findNextOperationIndex(std::vector<IRBinaryOperatorNode*>* operations) {
    for (int i = 0; i < operations->size(); ++i) {
        auto currentOp = operations->at(i);
        if (currentOp->isHandled()) continue;

        for (int j = i + 1; j < operations->size(); ++j) {
            auto otherOp = operations->at(j);
            if (!otherOp->isHandled() && otherOp->isHigherPriorityThan(currentOp)) {
                otherOp->markAsHandled();
                return new IRBinaryArithmeticNode(otherOp->getOp(), j, j+1);
            }
        }
        currentOp->markAsHandled();
        return new IRBinaryArithmeticNode(currentOp->getOp(), i, i+1);
    }
    throw std::logic_error("unable to find next binary arithmetic operation");
}

llvm::Value* LiteralIRBinaryArithmeticExpressionInjectorStrategy::calculate(IRBlockNode* irBlock, IRBinaryArithmeticNode* binaryOp, llvm::Value* leftValue, llvm::Value* rightValue, std::shared_ptr<IRModuleNode> irModule) {
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