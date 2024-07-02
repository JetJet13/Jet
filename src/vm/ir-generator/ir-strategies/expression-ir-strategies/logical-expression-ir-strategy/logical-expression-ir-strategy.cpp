//
// Created by Johny Georges on 2024-06-15.
//

#include "logical-expression-ir-strategy.h"

IRLogicalExpressionNode* LogicalExpressionIRStrategy::generate(ASTLogicalExpressionNode* node, std::unique_ptr<llvm::LLVMContext>*, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope);
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope);
    return new IRLogicalExpressionNode(node, llvm::BinaryOperator::Create(
            this->determineOperatorIR(node->getLogicalOperator()),
            leftExpressionIr->getIRValue(),
            rightExpressionIr->getIRValue()
    ));
}

llvm::Instruction::BinaryOps LogicalExpressionIRStrategy::determineOperatorIR(ASTLogicalOperatorNode *node) {
    if (node->isAnd()) {
        return llvm::Instruction::BinaryOps::And;
    }
    return llvm::Instruction::BinaryOps::Or;
}
