//
// Created by Johny Georges on 2024-06-15.
//

#include "logical-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

std::shared_ptr<IRLogicalExpressionNode> LogicalExpressionIRStrategy::generate(std::shared_ptr<ASTLogicalExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, std::shared_ptr<IROperation> irOperation) {
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope, irContext, irOperation);
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope, irContext, irOperation);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    return std::make_shared<IRLogicalExpressionNode>(node, llvm::BinaryOperator::Create(
            this->determineOperatorIR(node->getLogicalOperator()),
            irGenerator->generateBoolean(true), // placeholder
            irGenerator->generateBoolean(true) // placeholder
    ), irType, leftExpressionIr, rightExpressionIr);
}

llvm::Instruction::BinaryOps LogicalExpressionIRStrategy::determineOperatorIR(std::shared_ptr<ASTLogicalOperatorNode> node) {
    if (node->isAnd()) {
        return llvm::Instruction::BinaryOps::And;
    }
    return llvm::Instruction::BinaryOps::Or;
}
