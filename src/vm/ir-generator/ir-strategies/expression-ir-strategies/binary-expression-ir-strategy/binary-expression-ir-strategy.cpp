//
// Created by Johny Georges on 2024-06-15.
//

#include "binary-expression-ir-strategy.h"

llvm::Value* BinaryExpressionIRStrategy::generate(ASTBinaryExpressionNode* node, std::unique_ptr<llvm::LLVMContext>*, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope);
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope);
    if (node->getBinaryOperator()->isArithmetic()) {
        return llvm::BinaryOperator::Create(
                this->determineArithmeticOperatorIR(node->getBinaryOperator()),
                leftExpressionIr,
                rightExpressionIr
        );
    }

    return llvm::CmpInst::Create(
            llvm::Instruction::OtherOps::ICmp,
            this->determineComparatorPredicate(node->getBinaryOperator()),
            leftExpressionIr,
            rightExpressionIr
    );
}

llvm::Instruction::BinaryOps BinaryExpressionIRStrategy::determineArithmeticOperatorIR(ASTBinaryOperatorNode* operatorNode) {
    if (operatorNode->isPlus()) {
        return llvm::Instruction::BinaryOps::Add;
    } else if (operatorNode->isMinus()) {
        return llvm::Instruction::BinaryOps::Sub;
    } else if (operatorNode->isMultiply()) {
        return llvm::Instruction::BinaryOps::Mul;
    } else if (operatorNode->isDivide()) {
        return llvm::Instruction::BinaryOps::SDiv;
    } else if (operatorNode->isModulo()) {
        return llvm::Instruction::BinaryOps::SRem;
    }
    return llvm::Instruction::BinaryOps::BinaryOpsEnd;
}

llvm::CmpInst::Predicate BinaryExpressionIRStrategy::determineComparatorPredicate(ASTBinaryOperatorNode* operatorNode) {
    if (operatorNode->isEqual()) {
        return llvm::CmpInst::Predicate::ICMP_EQ;
    } else if (operatorNode->isNotEqual()) {
        return llvm::CmpInst::Predicate::ICMP_NE;
    } else if (operatorNode->isLessThan()) {
        return llvm::CmpInst::Predicate::ICMP_SLT;
    } else if (operatorNode->isLessThanOrEqual()) {
        return llvm::CmpInst::Predicate::ICMP_SLE;
    } else if (operatorNode->isGreaterThan()) {
        return llvm::CmpInst::Predicate::ICMP_SGT;
    } else if (operatorNode->isGreaterThanOrEqual()) {
        return llvm::CmpInst::Predicate::ICMP_SGE;
    }
    return llvm::CmpInst::Predicate::BAD_ICMP_PREDICATE;
}