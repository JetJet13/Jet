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
// Created by Johny Georges on 2024-07-13.
//

#include "function-return-expression-ir-strategy.h"

std::shared_ptr<IRFunctionReturnExpressionNode> FunctionReturnExpressionIRStrategy::generate(std::shared_ptr<ASTFunctionReturnExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    if (node->getExpression()) {
        auto irExpressionNode = irGenerator->generateFor(node->getExpression().value(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
        irExpressionNode->markAsReturned();
        return std::make_shared<IRFunctionReturnExpressionNode>(node, irExpressionNode);
    }
    return std::make_shared<IRFunctionReturnExpressionNode>(node);
}