//
// Created by Johny Georges on 2025-02-10.
//

#include "dref-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-dref-expression-node.h"

std::shared_ptr<IRExpressionNode> DrefExpressionIRStrategy::generate(std::shared_ptr<ASTDrefExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto irExpressionNode = irGenerator->generateFor(node->getExpressionNode(), scope, irContext, irOperation);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto allocation = this->generateAllocation(node, irType, irGenerator, irContext, irOperation);
    return std::make_shared<IRDrefExpressionNode>(node, irExpressionNode, irType, allocation);
}

std::shared_ptr<IRInstructionNode> DrefExpressionIRStrategy::generateAllocation(std::shared_ptr<ASTDrefExpressionNode> node, std::shared_ptr<IRType> irType, IRGenerator* irGenerator, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
}