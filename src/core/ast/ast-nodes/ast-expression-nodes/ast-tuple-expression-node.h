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
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_TUPLE_EXPRESSION_NODE_H
#define JETLANG_AST_TUPLE_EXPRESSION_NODE_H

#include <vector>
#include "ast-aggregate-expression-node.h"
#include "../ast-node.h"
#include "../ast-tuple-nodes/ast-tuple-list-start-node.h"
#include "../ast-tuple-nodes/ast-tuple-item-node.h"
#include "../ast-tuple-nodes/ast-tuple-list-end-node.h"
#include "../ast-comma-node.h"
#include "../../../type-signature/tuple-type-signature/tuple-type-signature.h"

class ASTTupleExpressionNode : public ASTAggregateExpressionNode {
private:
    std::shared_ptr<ASTTupleListStartNode> _tupleListStart;
    std::shared_ptr<ASTTupleListEndNode> _tupleListEnd;
    std::vector<std::shared_ptr<ASTCommaNode>> _commas;
    std::vector<std::shared_ptr<ASTTupleItemNode>> _items;
    std::shared_ptr<TupleTypeSignature> _typeSignature = std::make_shared<TupleTypeSignature>();
public:
    ASTTupleExpressionNode(std::shared_ptr<ASTTupleListStartNode> tupleListStart, std::shared_ptr<ASTTupleListEndNode> tupleListEnd);
    ASTTupleExpressionNode(std::shared_ptr<ASTTupleListStartNode> tupleListStart, std::vector<std::shared_ptr<ASTTupleItemNode>> items, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTTupleListEndNode> tupleListEnd);
    std::vector<std::shared_ptr<ASTTupleItemNode>>* getItems();
    uint64_t numItems();
    std::shared_ptr<ASTTupleExpressionNode> addItem(std::shared_ptr<ASTTupleItemNode> item);
    std::shared_ptr<ASTTupleExpressionNode> addComma(std::shared_ptr<ASTCommaNode> comma);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<TupleTypeSignature> getTupleTypeSignature();
    void setTypeSignature(std::shared_ptr<TupleTypeSignature> tupleTypeSignature);
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_EXPRESSION_NODE_H
