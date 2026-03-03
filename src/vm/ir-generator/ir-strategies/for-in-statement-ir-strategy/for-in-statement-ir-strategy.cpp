//
// Created by Johny Georges on 2025-05-24.
//

#include "for-in-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-for-in-statement-node/ir-for-in-statement-node.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../shared/utils/logger/logger.h"

IRStatementNode* ForInStatementIRStrategy::generate(ASTForInStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto sourceIRExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    auto index = IRInstructionNodeFactory::create(new IRType(irGenerator->generateIntType()));
    auto variableIrType = irGenerator->generateTypeFor(node->getVariable()->getTypeSignature(), scope, irContext);
    auto variable = IRInstructionNodeFactory::create(variableIrType);
    auto capturedVariable = std::optional<IRCapturedVariableNode*>();
    auto setupBlock = irGenerator->generateForInSetupBlock(irContext, scope);
    auto forInBlock = irGenerator->generateForInBlock(irContext, scope);
    auto bodyBlock = irGenerator->generateForInBodyBlock(irContext, scope);
    auto endBlock = irGenerator->generateForInEndBlock(irContext, scope);

    if (node->getVariable()->isCaptured()) {
        auto malloc = new IRInstructionNode(
            llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction(),
                {
                    irGenerator->generateInt64Constant(1),
                    irGenerator->generateInt64Constant(variableIrType->getSizeInBytes())
                }
            ),
            irGenerator->generateIrPointerType(variableIrType)
        );
        auto irArc = irGenerator->generateArcAllocation(irContext, node->getVariable()->getCaptureCount());
        capturedVariable = new IRCapturedVariableNode(malloc, irArc);
        setupBlock->getScope()->insert(node->getVariable()->getVariable()->getId(), capturedVariable.value()->getVariable());
        setupBlock->getScope()->insertArc(node->getVariable()->getVariable()->getId(), capturedVariable.value()->getArc());
        bodyBlock->getScope()->insert(node->getVariable()->getVariable()->getId(), capturedVariable.value()->getVariable());
        bodyBlock->getScope()->insertArc(node->getVariable()->getVariable()->getId(), capturedVariable.value()->getArc());
    } else {
        setupBlock->getScope()->insert(node->getVariable()->getVariable()->getId(), variable);
        bodyBlock->getScope()->insert(node->getVariable()->getVariable()->getId(), variable);
    }

    for (auto statement : *node->getBlock()->getContents()) {
        bodyBlock->insert(irGenerator->generateFor(statement, bodyBlock->getScope(), irContext));
    }
    return new IRForInStatementNode(node, index, variable, sourceIRExpression, setupBlock, forInBlock, bodyBlock, endBlock, capturedVariable);
}