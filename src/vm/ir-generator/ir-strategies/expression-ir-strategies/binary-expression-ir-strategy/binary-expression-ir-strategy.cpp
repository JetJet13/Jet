//
// Created by Johny Georges on 2024-06-15.
//

#include "binary-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-comparison-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-arithmetic-expression-node.h"

IRBinaryExpressionNode* BinaryExpressionIRStrategy::generate(ASTBinaryExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    if (node->getBinaryOperator()->isArithmetic()) {
        return new IRBinaryArithmeticExpressionNode(node, llvm::BinaryOperator::Create(
                this->determineArithmeticOperatorIR(node->getBinaryOperator()),
                leftExpressionIr->getValue(),
                rightExpressionIr->getValue()
        ), leftExpressionIr, rightExpressionIr, irType);
    }

    auto comparisonIrType = irGenerator->generateTypeFor(node->getLeftNode()->getTypeSignature(), scope, irContext);
    return new IRBinaryComparisonExpressionNode(node, llvm::CmpInst::Create(
            llvm::Instruction::OtherOps::ICmp,
            this->determineComparatorPredicate(node->getBinaryOperator()),
            leftExpressionIr->getValue(),
            rightExpressionIr->getValue()
    ), leftExpressionIr, rightExpressionIr, irType, comparisonIrType);
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