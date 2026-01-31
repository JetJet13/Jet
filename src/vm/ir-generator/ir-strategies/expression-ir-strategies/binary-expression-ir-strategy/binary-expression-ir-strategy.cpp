//
// Created by Johny Georges on 2024-06-15.
//

#include "binary-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-comparison-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-arithmetic-expression-node.h"
#include "../../../../../shared/utils/logger/logger.h"

IRBinaryExpressionNode* BinaryExpressionIRStrategy::generate(ASTBinaryExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto typeSignature = node->getLeftNode()->getTypeSignature()->getTargetTypeSignature();
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    if (node->getBinaryOperator()->isArithmetic()) {
        return new IRBinaryArithmeticExpressionNode(node, llvm::BinaryOperator::Create(
                this->determineArithmeticOperatorIR(node->getBinaryOperator(), typeSignature),
                leftExpressionIr->getValue(),
                rightExpressionIr->getValue()
        ), leftExpressionIr, rightExpressionIr, irType);
    }

    auto leftIrType = irGenerator->generateTypeFor(node->getLeftNode()->getTypeSignature(), scope, irContext);
    auto rightIrType = irGenerator->generateTypeFor(node->getRightNode()->getTypeSignature(), scope, irContext);
    return new IRBinaryComparisonExpressionNode(node, llvm::CmpInst::Create(
            typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
            ? llvm::Instruction::OtherOps::FCmp
            : llvm::Instruction::OtherOps::ICmp,
            this->determineComparatorPredicate(node->getBinaryOperator(), typeSignature),
            leftExpressionIr->getValue(),
            rightExpressionIr->getValue()
    ), leftExpressionIr, rightExpressionIr, irType, leftIrType, rightIrType);
}

llvm::Instruction::BinaryOps BinaryExpressionIRStrategy::determineArithmeticOperatorIR(ASTBinaryOperatorNode* operatorNode, TypeSignature* typeSignature) {
    if (operatorNode->isPlus()) {
        return typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::Instruction::BinaryOps::FAdd
        : llvm::Instruction::BinaryOps::Add;
    } else if (operatorNode->isMinus()) {
        return typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::Instruction::BinaryOps::FSub
        : llvm::Instruction::BinaryOps::Sub;
    } else if (operatorNode->isMultiply()) {
        return typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::Instruction::BinaryOps::FMul
        : llvm::Instruction::BinaryOps::Mul;
    } else if (operatorNode->isDivide()) {
        return typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::Instruction::BinaryOps::FDiv
        : llvm::Instruction::BinaryOps::SDiv;
    } else if (operatorNode->isModulo()) {
        return llvm::Instruction::BinaryOps::SRem;
    }
    return llvm::Instruction::BinaryOps::BinaryOpsEnd;
}

llvm::CmpInst::Predicate BinaryExpressionIRStrategy::determineComparatorPredicate(ASTBinaryOperatorNode* operatorNode, TypeSignature* typeSignature) {
    if (operatorNode->isEqual()) {
        return typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_OEQ
        : llvm::CmpInst::Predicate::ICMP_EQ;
    } else if (operatorNode->isNotEqual()) {
        return typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_ONE
        : llvm::CmpInst::Predicate::ICMP_EQ;
    } else if (operatorNode->isLessThan()) {
        return typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_OLT
        : llvm::CmpInst::Predicate::ICMP_SLT;
    } else if (operatorNode->isLessThanOrEqual()) {
        return typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_OLE
        : llvm::CmpInst::Predicate::ICMP_SLE;
    } else if (operatorNode->isGreaterThan()) {
        return typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_OGE
        : llvm::CmpInst::Predicate::ICMP_SGT;
    } else if (operatorNode->isGreaterThanOrEqual()) {
        return typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_OGE
        : llvm::CmpInst::Predicate::ICMP_SGE;
    }
    return llvm::CmpInst::Predicate::BAD_ICMP_PREDICATE;
}