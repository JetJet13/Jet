//
// Created by Johny Georges on 2025-02-10.
//

#include "ref-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-literal-expression-node.h"

IRRefExpressionNode* RefExpressionIRStrategy::generate(ASTRefExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto irExpressionNode = irGenerator->generateFor(node->getExpressionNode(), scope, irContext, IR_OPERAND_OP);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    return new IRRefExpressionNode(node, irExpressionNode, irType);
}