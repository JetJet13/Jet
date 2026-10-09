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
// Created by Johny Georges on 2024-01-12.
//

#ifndef JETLANG_AST_NODE_H
#define JETLANG_AST_NODE_H

#include <vector>
#include "../../lexeme/lexeme.h"
#include "../types/ast-node-type.h"
#include "../../pre-processor/syntax-analyzer/types/syntax-analyzer-mode.h"
#include "../../type-signature/type-signature.h"

class ASTNode : public std::enable_shared_from_this<ASTNode> {
protected:
    std::optional<std::shared_ptr<ASTNode>> _parentNode;
    ASTNodeType _nodeType;
    unsigned int _priority = 1;
    std::string _id;
    std::string _filePath;
    std::vector<std::shared_ptr<ASTNode>> _children = {};
    bool _isGlobal = false;
    bool _isGrouped = false;
public:
    std::string getId();
    std::string getFilePath();
    std::shared_ptr<ASTNode> setId(std::string id);
    std::shared_ptr<ASTNode> setFilePath(std::string filePath);
    std::optional<std::shared_ptr<ASTNode>> getParentNode();
    void setParentNode(std::shared_ptr<ASTNode> parentNode);
    void markAsGlobal();
    void markAsGrouped();
    virtual ASTNodeType getNodeType() = 0;
    virtual std::string toString() = 0;
    virtual std::shared_ptr<Position> getStartPosition();
    virtual std::shared_ptr<Position> getEndPosition();
    virtual std::string getLineColumn();
    virtual bool isSameAs(std::shared_ptr<ASTNode> other);
    virtual bool isExpression();
    virtual bool isScopedBlockNode();
    virtual void print();
    virtual std::string toSourceCode();
    virtual std::shared_ptr<TypeSignature> getTypeSignature();
    virtual std::vector<std::shared_ptr<ASTNode>> getChildren();
    virtual std::shared_ptr<ASTNode> transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode);
    virtual bool isExportable();
    virtual bool isGlobal();
    bool isGrouped();
    bool is(ASTNodeType astNodeType);
    bool isOneOf(std::vector<ASTNodeType> astNodeTypes);
    bool isSameNodeTypeAs(std::shared_ptr<ASTNode> other);
    unsigned int getPriority();
    bool isHigherPriorityThan(std::shared_ptr<ASTNode> other);
    bool isLowerPriorityThan(std::shared_ptr<ASTNode> other);
};
#endif //JETLANG_AST_NODE_H
