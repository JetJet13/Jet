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
// Created by Johny Georges on 2024-06-25.
//

#include "unary-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-unary-expression-nodes/ir-unary-negate-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-unary-expression-nodes/ir-unary-arithmetic-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRUnaryExpressionNode> UnaryExpressionIRStrategy::generate(std::shared_ptr<ASTUnaryExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto expressionIr = irGenerator->generateFor(node->getExpressionNode(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);

    auto sourceTypeSignature = node->getTypeSignature()->getTargetTypeSignature();
    if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
        sourceTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature)->getUnderlyingType());
    }


    if (node->getUnaryOperatorNode()->isPlus()) {
        if (sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)) {
            return std::make_shared<IRUnaryArithmeticExpressionNode>(node, llvm::BinaryOperator::Create(
                    llvm::Instruction::BinaryOps::FMul,
                    irGenerator->generateFloatConstant(1),
                    irGenerator->generateFloatConstant(1) // placeholder
            ), expressionIr, irType);
        }
        return std::make_shared<IRUnaryArithmeticExpressionNode>(node, llvm::BinaryOperator::Create(
                llvm::Instruction::BinaryOps::Mul,
                irGenerator->generateInt64Constant(1),
                irGenerator->generateInt64Constant(1) // placeholder
        ), expressionIr, irType);
    } else if (node->getUnaryOperatorNode()->isMinus()) {
        if (sourceTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)) {
            return std::make_shared<IRUnaryArithmeticExpressionNode>(node, llvm::BinaryOperator::Create(
                    llvm::Instruction::BinaryOps::FSub,
                    irGenerator->generateFloatConstant(0),
                    irGenerator->generateFloatConstant(0) // placeholder
            ), expressionIr, irType);
        }
        return std::make_shared<IRUnaryArithmeticExpressionNode>(node, llvm::BinaryOperator::Create(
                llvm::Instruction::BinaryOps::Sub,
                irGenerator->generateInt64Constant(0),
                irGenerator->generateInt64Constant(0) // placeholder
        ), expressionIr, irType);
    } else {
        return std::make_shared<IRUnaryNegateExpressionNode>(node, expressionIr, irType);
    }
}