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
// Created by Johny Georges on 2026-03-14.
//

#ifndef JETLANG_AST_TUPLE_TYPE_NODE_H
#define JETLANG_AST_TUPLE_TYPE_NODE_H

#include <string>
#include "../ast-type-base-node.h"
#include "ast-tuple-type-start-node.h"
#include "ast-tuple-type-end-node.h"
#include "../../ast-comma-node.h"
#include "../ast-type-node.h"

class ASTTupleTypeNode : public ASTTypeBaseNode {
private:
    std::shared_ptr<ASTTupleTypeStartNode> _tupleTypeStartNode;
    std::shared_ptr<ASTTupleTypeEndNode> _tupleTypeEndNode;
    std::vector<std::shared_ptr<ASTCommaNode>> _commas;
    std::vector<std::shared_ptr<ASTTypeNode>> _types;
public:
    ASTTupleTypeNode(std::shared_ptr<ASTTupleTypeStartNode> tupleTypeStartNode, std::shared_ptr<ASTTupleTypeEndNode> tupleTypeEndNode);
    ASTTupleTypeNode(std::shared_ptr<ASTTupleTypeStartNode> tupleTypeStartNode, std::vector<std::shared_ptr<ASTTypeNode>> keyValueTypes, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTTupleTypeEndNode> tupleTypeEndNode);
    std::vector<std::shared_ptr<ASTTypeNode>> getValueTypes();
    uint64_t numValueTypes();
    std::shared_ptr<ASTTupleTypeNode> addComma(std::shared_ptr<ASTCommaNode> comma);
    std::shared_ptr<ASTTupleTypeNode> addValueType(std::shared_ptr<ASTTypeNode> type);
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_TYPE_NODE_H
