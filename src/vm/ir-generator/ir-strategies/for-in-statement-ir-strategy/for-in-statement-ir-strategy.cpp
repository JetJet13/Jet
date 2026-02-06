//
// Created by Johny Georges on 2025-05-24.
//

#include "for-in-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-for-in-statement-node/ir-for-in-statement-node.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../shared/utils/logger/logger.h"

IRStatementNode* ForInStatementIRStrategy::generate(ASTForInStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto forInScope = new IRLookupTable(scope);
    auto sourceIRExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    auto index = IRInstructionNodeFactory::create(new IRType(irGenerator->generateIntType()));
    auto variableIrType = irGenerator->generateTypeFor(node->getVariable()->getTypeSignature(), scope, irContext);
    auto variable = IRInstructionNodeFactory::create(variableIrType);
    auto capturedVariable = std::optional<IRCapturedVariableNode*>();
    auto setupBlock = irGenerator->generateForInSetupBlock(irContext);
    auto forInBlock = irGenerator->generateForInBlock(irContext);
    auto bodyBlock = irGenerator->generateForInBodyBlock(irContext);
    auto endBlock = irGenerator->generateForInEndBlock(irContext);

    if (node->getVariable()->isReferenced() || node->getVariable()->isCaptured()) {
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
        forInScope->insert(node->getVariable()->getVariable()->getId(), capturedVariable.value()->getVariable());
        forInScope->insertArc(node->getVariable()->getVariable()->getId(), capturedVariable.value()->getArc());
    } else {
        forInScope->insert(node->getVariable()->getVariable()->getId(), variable);
    }

    for (auto statement : *node->getBlock()->getContents()) {
        bodyBlock->insert(irGenerator->generateFor(statement, forInScope, irContext));
    }
    return new IRForInStatementNode(node, index, variable, sourceIRExpression, setupBlock, forInBlock, bodyBlock, endBlock, forInScope, capturedVariable);
}