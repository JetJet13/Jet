//
// Created by Johny Georges on 2024-06-15.
//

#include "binary-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-comparison-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-arithmetic-expression-node.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRBinaryExpressionNode> BinaryExpressionIRStrategy::generate(std::shared_ptr<ASTBinaryArithmeticExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto typeSignature = node->getLeftNode()->getTypeSignature()->getTargetTypeSignature();
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    auto binaryOperator = typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
            ? llvm::BinaryOperator::Create(
                    this->determineArithmeticOperatorIR(node->getBinaryOperator(), typeSignature),
                    irGenerator->generateFloatConstant(0),
                    irGenerator->generateFloatConstant(0)
            )
            : llvm::BinaryOperator::Create(
                    this->determineArithmeticOperatorIR(node->getBinaryOperator(), typeSignature),
                    irGenerator->generateIntConstant(0),
                    irGenerator->generateIntConstant(0)
            );

    auto binaryArithmeticExpressionNode = std::make_shared<IRBinaryArithmeticExpressionNode>(node, binaryOperator, leftExpressionIr, rightExpressionIr, irType);
    if (node->isGrouped()) {
        binaryArithmeticExpressionNode->markAsGrouped();
    }
    return binaryArithmeticExpressionNode;
}

std::shared_ptr<IRBinaryExpressionNode> BinaryExpressionIRStrategy::generate(std::shared_ptr<ASTBinaryComparatorExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto typeSignature = node->getLeftNode()->getTypeSignature()->getTargetTypeSignature();
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));

    auto leftIrType = irGenerator->generateTypeFor(node->getLeftNode()->getTypeSignature(), scope, irContext);
    auto rightIrType = irGenerator->generateTypeFor(node->getRightNode()->getTypeSignature(), scope, irContext);
    auto comparison = typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
            ? llvm::CmpInst::Create(
                    llvm::Instruction::OtherOps::FCmp,
                    this->determineComparatorPredicate(node->getBinaryOperator(), typeSignature),
                    irGenerator->generateFloatConstant(0), // placeholder
                    irGenerator->generateFloatConstant(0) // placeholder
            )
            : llvm::CmpInst::Create(
                    llvm::Instruction::OtherOps::ICmp,
                    this->determineComparatorPredicate(node->getBinaryOperator(), typeSignature),
                    irGenerator->generateIntConstant(0), // placeholder
                    irGenerator->generateIntConstant(0) // placeholder
            );
    return std::make_shared<IRBinaryComparisonExpressionNode>(node, comparison, leftExpressionIr, rightExpressionIr, irType, leftIrType, rightIrType);
}

llvm::Instruction::BinaryOps BinaryExpressionIRStrategy::determineArithmeticOperatorIR(std::shared_ptr<ASTBinaryArithmeticOperatorNode> operatorNode, std::shared_ptr<TypeSignature> typeSignature) {
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

llvm::CmpInst::Predicate BinaryExpressionIRStrategy::determineComparatorPredicate(std::shared_ptr<ASTBinaryComparatorOperatorNode> operatorNode, std::shared_ptr<TypeSignature> typeSignature) {
    if (operatorNode->isEqual()) {
        return typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_OEQ
        : llvm::CmpInst::Predicate::ICMP_EQ;
    } else if (operatorNode->isNotEqual()) {
        return typeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_ONE
        : llvm::CmpInst::Predicate::ICMP_NE;
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