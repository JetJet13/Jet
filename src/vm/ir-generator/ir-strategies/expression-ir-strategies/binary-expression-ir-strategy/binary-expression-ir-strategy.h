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

#ifndef JETLANG_BINARY_EXPRESSION_IR_STRATEGY_H
#define JETLANG_BINARY_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-binary-arithmetic-expression-node.h"
#include "../../../ir-generator.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-expression-node.h"
#include "../../../../../core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-binary-comparator-operator-node.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-binary-comparator-expression-node.h"

class BinaryExpressionIRStrategy {
private:
    llvm::Instruction::BinaryOps determineArithmeticOperatorIR(std::shared_ptr<ASTBinaryArithmeticOperatorNode> operatorNode, std::shared_ptr<TypeSignature> typeSignature);
    llvm::CmpInst::Predicate determineComparatorPredicate(std::shared_ptr<ASTBinaryComparatorOperatorNode> operatorNode, std::shared_ptr<TypeSignature> typeSignature);
public:
    std::shared_ptr<IRBinaryExpressionNode> generate(std::shared_ptr<ASTBinaryArithmeticExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
    std::shared_ptr<IRBinaryExpressionNode> generate(std::shared_ptr<ASTBinaryComparatorExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_BINARY_EXPRESSION_IR_STRATEGY_H
