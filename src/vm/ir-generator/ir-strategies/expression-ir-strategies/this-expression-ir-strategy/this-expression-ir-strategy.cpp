//
// Created by Johny Georges on 2026-06-15.
//

#include "this-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-this-expression-node.h"

std::shared_ptr<IRExpressionNode> ThisExpressionIRStrategy::generate(std::shared_ptr<ASTThisExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    return std::make_shared<IRThisExpressionNode>(node, scope->getClassScope().value());
}