//
// Created by Johny Georges on 2025-02-10.
//

#include "dref-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-dref-expression-node.h"

IRExpressionNode* DrefExpressionIRStrategy::generate(ASTDrefExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto irExpressionNode = irGenerator->generateFor(node->getExpressionNode(), scope, irContext, irOperationType);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    return new IRDrefExpressionNode(node, irExpressionNode, irType);
}