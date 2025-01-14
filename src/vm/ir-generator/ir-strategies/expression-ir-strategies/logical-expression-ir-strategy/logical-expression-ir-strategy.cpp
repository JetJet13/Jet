//
// Created by Johny Georges on 2024-06-15.
//

#include "logical-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRLogicalExpressionNode* LogicalExpressionIRStrategy::generate(ASTLogicalExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope, irContext, irOperationType);
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope, irContext, irOperationType);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    return new IRLogicalExpressionNode(node, llvm::BinaryOperator::Create(
            this->determineOperatorIR(node->getLogicalOperator()),
            leftExpressionIr->getValue(),
            rightExpressionIr->getValue()
    ), irType, leftExpressionIr, rightExpressionIr);
}

llvm::Instruction::BinaryOps LogicalExpressionIRStrategy::determineOperatorIR(ASTLogicalOperatorNode *node) {
    if (node->isAnd()) {
        return llvm::Instruction::BinaryOps::And;
    }
    return llvm::Instruction::BinaryOps::Or;
}
