//
// Created by Johny Georges on 2024-06-25.
//

#include "unary-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-unary-expression-nodes/ir-unary-negate-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-unary-expression-nodes/ir-unary-arithmetic-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRUnaryExpressionNode> UnaryExpressionIRStrategy::generate(std::shared_ptr<ASTUnaryExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, IROperation* irOperation) {
    auto expressionIr = irGenerator->generateFor(node->getExpressionNode(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (node->getUnaryOperatorNode()->isPlus()) {
        return std::make_shared<IRUnaryArithmeticExpressionNode>(node, llvm::BinaryOperator::Create(
                llvm::Instruction::BinaryOps::Mul,
                irGenerator->generateInt64Constant(1),
                irGenerator->generateInt64Constant(1) // placeholder
        ), expressionIr, irType);
    } else if (node->getUnaryOperatorNode()->isMinus()) {
        auto isFloat = node->getTypeSignature()->getTargetTypeSignature()->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE);
        if (isFloat) {
            return std::make_shared<IRUnaryArithmeticExpressionNode>(node, llvm::BinaryOperator::Create(
                    llvm::Instruction::BinaryOps::FSub,
                    irGenerator->generateFloatConstant(0),
                    irGenerator->generateFloatConstant(0) // placeholder
            ), expressionIr, irType);
        }
        return std::make_shared<IRUnaryArithmeticExpressionNode>(node, llvm::BinaryOperator::Create(
                llvm::Instruction::BinaryOps::Sub,
                irGenerator->generateInt64Constant(0),
                irGenerator->generateInt64Constant(0) // placeholder
        ), expressionIr, irType);
    } else {
        return std::make_shared<IRUnaryNegateExpressionNode>(node, expressionIr, irType);
    }
}