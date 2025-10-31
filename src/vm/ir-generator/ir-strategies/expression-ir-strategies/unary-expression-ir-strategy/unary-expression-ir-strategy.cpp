//
// Created by Johny Georges on 2024-06-25.
//

#include "unary-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-unary-expression-nodes/ir-unary-negate-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-unary-expression-nodes/ir-unary-arithmetic-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRUnaryExpressionNode* UnaryExpressionIRStrategy::generate(ASTUnaryExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto expressionIr = irGenerator->generateFor(node->getExpressionNode(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (node->getUnaryOperatorNode()->isPlus()) {
        return new IRUnaryArithmeticExpressionNode(node, llvm::BinaryOperator::Create(
                llvm::Instruction::BinaryOps::Mul,
                llvm::ConstantInt::get(**irContext->getContext(), llvm::APInt(64, 1)),
                expressionIr->getValue()
        ), expressionIr, irType);
    } else if (node->getUnaryOperatorNode()->isMinus()) {
        return new IRUnaryArithmeticExpressionNode(node, llvm::BinaryOperator::Create(
                llvm::Instruction::BinaryOps::Mul,
                llvm::ConstantInt::get(**irContext->getContext(), llvm::APInt(64, -1, true)),
                expressionIr->getValue()
        ), expressionIr, irType);
    } else {
        return new IRUnaryNegateExpressionNode(node, expressionIr, irType);
    }
}