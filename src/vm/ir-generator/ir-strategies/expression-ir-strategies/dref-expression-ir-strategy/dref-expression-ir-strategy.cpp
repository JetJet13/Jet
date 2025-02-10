//
// Created by Johny Georges on 2025-02-10.
//

#include "dref-expression-ir-strategy.h"

IRExpressionNode* DrefExpressionIRStrategy::generate(ASTDrefExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    return irGenerator->generateFor(node->getExpressionNode(), scope, irContext, IR_COPY_ASSIGNMENT_OP);
}