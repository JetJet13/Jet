//
// Created by Johny Georges on 2025-05-24.
//

#include "for-in-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-for-in-statement-node/ir-for-in-statement-node.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRStatementNode* ForInStatementIRStrategy::generate(ASTForInStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto sourceIRExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, IR_OPERAND_OP);
    auto index = IRInstructionNodeFactory::create(new IRType(irGenerator->generateIntType()));
    auto variableIrType = irGenerator->generateTypeFor(node->getVariable()->getTypeSignature(), scope, irContext);
    auto variable = IRInstructionNodeFactory::create(variableIrType);
    auto setupBlock = irGenerator->generateForInSetupBlock(irContext);
    auto forInBlock = irGenerator->generateForInBlock(irContext);
    auto bodyBlock = irGenerator->generateForInBodyBlock(irContext);
    auto endBlock = irGenerator->generateForInEndBlock(irContext);

    auto bodyScope = new IRLookupTable(scope);
    bodyScope->insert(node->getVariable()->getVariable()->getId(), variable);
    for (auto statement : *node->getBlock()->getContents()) {
        bodyBlock->insert(irGenerator->generateFor(statement, bodyScope, irContext));
    }
    return new IRForInStatementNode(node, index, variable, sourceIRExpression, setupBlock, forInBlock, bodyBlock, endBlock);
}