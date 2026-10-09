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

#include "ir-function-return-expression-node.h"

IRFunctionReturnExpressionNode::IRFunctionReturnExpressionNode(std::shared_ptr<ASTFunctionReturnExpressionNode> node, std::optional<std::shared_ptr<IRExpressionNode>> irExpression) {
    _node = node;
    _irExpression = irExpression;
}

std::optional<std::shared_ptr<IRExpressionNode>> IRFunctionReturnExpressionNode::getReturnExpression() {
    return _irExpression;
}

IRNodeType IRFunctionReturnExpressionNode::getNodeType() {
    return IR_FUNCTION_RETURN_EXPRESSION_NODE;
}

std::string IRFunctionReturnExpressionNode::toString() {
    return "IR_FUNCTION_RETURN_EXPRESSION_NODE";
}

void IRFunctionReturnExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    if (_irExpression) {
        _irExpression.value()->print(stream);
    }
}