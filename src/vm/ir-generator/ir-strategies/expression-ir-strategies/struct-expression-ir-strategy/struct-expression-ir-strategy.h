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
// Created by Johny Georges on 2024-06-21.
//

#ifndef JETLANG_STRUCT_EXPRESSION_IR_STRATEGY_H
#define JETLANG_STRUCT_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-struct-expression-node.h"

class StructExpressionIRStrategy {
private:
    std::shared_ptr<IRInstructionNode> generateStructAllocation(std::shared_ptr<IRStructType> irType, std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> structValueSourceAllocationMap, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext);
    std::shared_ptr<IRInstructionNode> generateStructRefAllocation(std::shared_ptr<ASTStructExpressionNode> node, std::shared_ptr<IRStructRefType> irType, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
public:
    std::shared_ptr<IRStructExpressionNode> generate(std::shared_ptr<ASTStructExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_STRUCT_EXPRESSION_IR_STRATEGY_H
