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
// Created by Johny Georges on 2025-06-28.
//

#ifndef JETLANG_AST_STRUCT_TYPE_NODE_H
#define JETLANG_AST_STRUCT_TYPE_NODE_H

#include <string>
#include "../ast-type-base-node.h"
#include "ast-struct-type-start-node.h"
#include "ast-struct-type-end-node.h"
#include "ast-struct-type-key-value-node.h"
#include "../../ast-comma-node.h"

class ASTStructTypeNode : public ASTTypeBaseNode {
protected:
    std::shared_ptr<ASTStructTypeStartNode> _structTypeStartNode;
    std::shared_ptr<ASTStructTypeEndNode> _structTypeEndNode;
    std::vector<std::shared_ptr<ASTCommaNode>> _commas;
    std::vector<std::shared_ptr<ASTStructTypeKeyValueNode>> _keyValueTypes;
public:
    ASTStructTypeNode(std::shared_ptr<ASTStructTypeStartNode> structTypeStartNode, std::shared_ptr<ASTStructTypeEndNode> structTypeEndNode);
    ASTStructTypeNode(std::shared_ptr<ASTStructTypeStartNode> structTypeStartNode, std::vector<std::shared_ptr<ASTStructTypeKeyValueNode>> keyValueTypes, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTStructTypeEndNode> structTypeEndNode);
    std::vector<std::shared_ptr<ASTStructTypeKeyValueNode>> getKeyValueTypes();
    uint64_t numKeyValueTypes();
    std::shared_ptr<ASTStructTypeNode> addKeyValueType(std::shared_ptr<ASTStructTypeKeyValueNode> keyValueType);
    std::shared_ptr<ASTStructTypeNode> addComma(std::shared_ptr<ASTCommaNode> comma);
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_STRUCT_TYPE_NODE_H
