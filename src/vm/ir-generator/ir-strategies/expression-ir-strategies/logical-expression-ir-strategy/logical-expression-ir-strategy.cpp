//
// Created by Johny Georges on 2024-06-15.
//

#include "logical-expression-ir-strategy.h"

llvm::Value* LogicalExpressionIRStrategy::generate(ASTLogicalExpressionNode* node, std::unique_ptr<llvm::LLVMContext>*, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope);
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope);
    return llvm::BinaryOperator::Create(
            this->determineOperatorIR(node->getLogicalOperator()),
            leftExpressionIr,
            rightExpressionIr
    );
}

llvm::Instruction::BinaryOps LogicalExpressionIRStrategy::determineOperatorIR(ASTLogicalOperatorNode *node) {
    if (node->isAnd()) {
        return llvm::Instruction::BinaryOps::And;
    }
    return llvm::Instruction::BinaryOps::Or;
}
