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
// Created by Johny Georges on 2024-03-12.
//

#ifndef JETLANG_AST_STRUCT_EXPRESSION_NODE_H
#define JETLANG_AST_STRUCT_EXPRESSION_NODE_H

#include <unordered_map>
#include "../ast-node.h"
#include "../ast-struct-nodes/ast-struct-key-value-node.h"
#include "../ast-struct-nodes/ast-struct-start-node.h"
#include "../ast-struct-nodes/ast-struct-end-node.h"
#include "../../../type-signature/struct-type-signature/struct-type-signature.h"
#include "ast-aggregate-expression-node.h"
#include "../ast-comma-node.h"

class ASTStructExpressionNode : public ASTAggregateExpressionNode {
private:
    std::shared_ptr<ASTStructStartNode> _structStartNode;
    std::shared_ptr<ASTStructEndNode> _structEndNode;
    std::vector<std::shared_ptr<ASTStructKeyValueNode>> _keyValuePairs;
    std::vector<std::shared_ptr<ASTCommaNode>> _commas;
    std::shared_ptr<StructTypeSignature> _typeSignature = std::make_shared<StructTypeSignature>();
public:
    ASTStructExpressionNode(std::shared_ptr<ASTStructStartNode> structStartNode, std::shared_ptr<ASTStructEndNode> structEndNode);
    ASTStructExpressionNode(std::shared_ptr<ASTStructStartNode> structStartNode, std::vector<std::shared_ptr<ASTStructKeyValueNode>> keyValuePairs, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTStructEndNode> structEndNode);
    std::vector<std::shared_ptr<ASTStructKeyValueNode>> getKeyValuePairs();
    std::shared_ptr<ASTStructKeyValueNode> getKeyValuePairAt(uint64_t index);
    std::shared_ptr<ASTStructExpressionNode> addKeyValuePair(std::shared_ptr<ASTStructKeyValueNode> keyValuePair);
    std::shared_ptr<ASTStructExpressionNode> addComma(std::shared_ptr<ASTCommaNode> comma);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<StructTypeSignature> getStructTypeSignature();
    void setTypeSignature(std::shared_ptr<StructTypeSignature> structTypeSignature);
    uint64_t size();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_STRUCT_EXPRESSION_NODE_H
