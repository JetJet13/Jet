//
// Created by Johny Georges on 2024-06-25.
//

#include "unary-expression-ir-strategy.h"

llvm::Value* UnaryExpressionIRStrategy::generate(ASTUnaryExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto expressionIr = irGenerator->generateFor(node->getExpressionNode(), scope);

    if (node->getUnaryOperatorNode()->isPlus()) {
        return llvm::BinaryOperator::Create(
                llvm::Instruction::BinaryOps::Mul,
                llvm::ConstantInt::get(**context, llvm::APInt(32, 1)),
                expressionIr
        );
    } else if (node->getUnaryOperatorNode()->isMinus()) {
        return llvm::BinaryOperator::Create(
                llvm::Instruction::BinaryOps::Mul,
                llvm::ConstantInt::get(**context, llvm::APInt(32, -1, true)),
                expressionIr
        );
    } else {
        return llvm::UnaryOperator::Create(
                llvm::Instruction::UnaryOps::FNeg,
                expressionIr
        );
    }
}