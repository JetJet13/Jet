//
// Created by Johny Georges on 2024-11-25.
//

#include "expression-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-expression-statement-node.h"

std::shared_ptr<IRStatementNode> ExpressionStatementIRStrategy::generate(std::shared_ptr<ASTExpressionStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return std::make_shared<IRExpressionStatementNode>(node, irGenerator->generateFor(node->getExpression(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP)));
}