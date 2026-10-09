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
// Created by Johny Georges on 2024-06-17.
//

#ifndef JETLANG_ARRAY_EXPRESSION_IR_STRATEGY_H
#define JETLANG_ARRAY_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-expression-node.h"
#include "../../../../ir-type/ir-array-type.h"

class ArrayExpressionIRStrategy {
private:
    std::shared_ptr<IRInstructionNode> generateArrayAllocation(std::shared_ptr<ASTArrayExpressionNode> node, std::shared_ptr<IRArrayPointerType> irArrayPointerType, std::shared_ptr<IRArrayType> irArrayType, std::shared_ptr<IRType> arrayElementIrType, std::vector<std::shared_ptr<IRInstructionNode>> childAllocations, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
    std::shared_ptr<IRInstructionNode> generateArrayPointerAllocation(std::shared_ptr<ASTArrayExpressionNode> node, std::shared_ptr<IRArrayPointerType> irArrayPointerType, std::shared_ptr<IRArrayType> irArrayType, std::shared_ptr<IRInstructionNode> arrayAllocation, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
public:
    std::shared_ptr<IRArrayExpressionNode> generate(std::shared_ptr<ASTArrayExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_ARRAY_EXPRESSION_IR_STRATEGY_H
