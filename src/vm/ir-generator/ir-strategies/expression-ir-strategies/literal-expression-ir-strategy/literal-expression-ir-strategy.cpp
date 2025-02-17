//
// Created by Johny Georges on 2024-07-02.
//

#include "literal-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-literal-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-string-literal-expression-node.h"

IRExpressionNode* LiteralExpressionIRStrategy::generate(ASTLiteralExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto irLiteralNode = irGenerator->generateFor(node->getLiteralNode(), scope, irContext);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (irLiteralNode->is(IR_STRING_LITERAL_NODE)) {
        auto sourceAllocation = IRInstructionNodeFactory::create(irLiteralNode->getIRType());
        auto arrayPointerSourceAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType), sourceAllocation);
        return new IRStringLiteralExpressionNode(node, (IRStringLiteralNode*)irLiteralNode, (IRArrayPointerType*)irType, sourceAllocation, arrayPointerSourceAllocation);
    }
    return new IRLiteralExpressionNode(node, irLiteralNode, irType);
}