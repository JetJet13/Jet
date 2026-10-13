// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-06-15.
//

#include "binary-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-comparison-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-arithmetic-expression-node.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRBinaryExpressionNode> BinaryExpressionIRStrategy::generate(std::shared_ptr<ASTBinaryArithmeticExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));

    auto sourceTypeSignature = node->getLeftNode()->getTypeSignature()->getTargetTypeSignature();
    if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
        sourceTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature)->getUnderlyingType());
    }


    auto binaryOperator = sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
            ? llvm::BinaryOperator::Create(
                    this->determineArithmeticOperatorIR(node->getBinaryOperator(), sourceTypeSignature),
                    irGenerator->generateFloatConstant(0),
                    irGenerator->generateFloatConstant(0)
            )
            : llvm::BinaryOperator::Create(
                    this->determineArithmeticOperatorIR(node->getBinaryOperator(), sourceTypeSignature),
                    irGenerator->generateIntConstant(0),
                    irGenerator->generateIntConstant(0)
            );

    auto binaryArithmeticExpressionNode = std::make_shared<IRBinaryArithmeticExpressionNode>(node, binaryOperator, leftExpressionIr, rightExpressionIr, irType);
    if (node->isGrouped()) {
        binaryArithmeticExpressionNode->markAsGrouped();
    }
    return binaryArithmeticExpressionNode;
}

std::shared_ptr<IRBinaryExpressionNode> BinaryExpressionIRStrategy::generate(std::shared_ptr<ASTBinaryComparatorExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto typeSignature = node->getLeftNode()->getTypeSignature()->getTargetTypeSignature();
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));

    auto leftIrType = irGenerator->generateTypeFor(node->getLeftNode()->getTypeSignature(), scope, irContext);
    auto rightIrType = irGenerator->generateTypeFor(node->getRightNode()->getTypeSignature(), scope, irContext);

    auto sourceTypeSignature = typeSignature;
    if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
        sourceTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature)->getUnderlyingType());
    }


    auto comparison = sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
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
    auto sourceTypeSignature = typeSignature;
    if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
        sourceTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature)->getUnderlyingType());
    }

    if (operatorNode->isPlus()) {
        return sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::Instruction::BinaryOps::FAdd
        : llvm::Instruction::BinaryOps::Add;
    } else if (operatorNode->isMinus()) {
        return sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::Instruction::BinaryOps::FSub
        : llvm::Instruction::BinaryOps::Sub;
    } else if (operatorNode->isMultiply()) {
        return sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::Instruction::BinaryOps::FMul
        : llvm::Instruction::BinaryOps::Mul;
    } else if (operatorNode->isDivide()) {
        return sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::Instruction::BinaryOps::FDiv
        : llvm::Instruction::BinaryOps::SDiv;
    } else if (operatorNode->isModulo()) {
        return llvm::Instruction::BinaryOps::SRem;
    }
    return llvm::Instruction::BinaryOps::BinaryOpsEnd;
}

llvm::CmpInst::Predicate BinaryExpressionIRStrategy::determineComparatorPredicate(std::shared_ptr<ASTBinaryComparatorOperatorNode> operatorNode, std::shared_ptr<TypeSignature> typeSignature) {
    auto sourceTypeSignature = typeSignature;
    if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
        sourceTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature)->getUnderlyingType());
    }

    if (operatorNode->isEqual()) {
        return sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_OEQ
        : llvm::CmpInst::Predicate::ICMP_EQ;
    } else if (operatorNode->isNotEqual()) {
        return sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_ONE
        : llvm::CmpInst::Predicate::ICMP_NE;
    } else if (operatorNode->isLessThan()) {
        return sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_OLT
        : llvm::CmpInst::Predicate::ICMP_SLT;
    } else if (operatorNode->isLessThanOrEqual()) {
        return sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_OLE
        : llvm::CmpInst::Predicate::ICMP_SLE;
    } else if (operatorNode->isGreaterThan()) {
        return sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_OGE
        : llvm::CmpInst::Predicate::ICMP_SGT;
    } else if (operatorNode->isGreaterThanOrEqual()) {
        return sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)
        ? llvm::CmpInst::Predicate::FCMP_OGE
        : llvm::CmpInst::Predicate::ICMP_SGE;
    }
    return llvm::CmpInst::Predicate::BAD_ICMP_PREDICATE;
}