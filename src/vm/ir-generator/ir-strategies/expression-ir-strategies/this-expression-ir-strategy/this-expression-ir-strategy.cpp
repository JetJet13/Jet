//
// Created by Johny Georges on 2026-06-15.
//

#include "this-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-this-expression-node.h"

IRExpressionNode* ThisExpressionIRStrategy::generate(std::shared_ptr<ASTThisExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    return new IRThisExpressionNode(node, scope->getClassScope().value());
}