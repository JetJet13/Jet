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
// Created by Johny Georges on 2024-03-07.
//

#include "ast-group-end-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-end-node.h"
#include "../ast-function-nodes/ast-function-argument-list-end-node.h"
#include "../ast-type-nodes/ast-lambda-type-nodes/ast-lambda-type-parameter-list-end-node.h"

std::shared_ptr<ASTNode> ASTGroupEndNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_LAMBDA_TYPE_PARAMETER_LIST_MODE) {
        return std::make_shared<ASTLambdaTypeParameterListEndNode>(this->getLexeme());
    }

    if (mode == SA_FUNCTION_PARAMETER_LIST_MODE) {
        return std::make_shared<ASTFunctionParameterListEndNode>(this->getLexeme());
    }

    if (mode == SA_FUNCTION_ARGUMENT_LIST_MODE) {
        return std::make_shared<ASTFunctionArgumentListEndNode>(this->getLexeme());
    }

    if (nextNode && nextNode.value()->isOneOf({ AST_LAMBDA_FAT_ARROW_NODE, AST_BLOCK_START_NODE })) {
        return std::make_shared<ASTFunctionParameterListEndNode>(this->getLexeme());
    }

    return shared_from_this();
}

ASTNodeType ASTGroupEndNode::getNodeType() {
    return AST_GROUP_END_NODE;
}

std::string ASTGroupEndNode::toString() {
    return "GROUP_END";
}
