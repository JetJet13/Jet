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
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_AST_INTERFACE_PROPERTY_LIST_NODE_H
#define JETLANG_AST_INTERFACE_PROPERTY_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-interface-start-node.h"
#include "ast-interface-end-node.h"
#include "ast-interface-property-node.h"
#include "../ast-comma-node.h"

class ASTInterfacePropertyListNode : public ASTNode {
private:
    std::shared_ptr<ASTInterfaceStartNode> _startNode;
    std::shared_ptr<ASTInterfaceEndNode> _endNode;
    std::vector<std::shared_ptr<ASTCommaNode>> _commas;
    std::vector<std::shared_ptr<ASTInterfacePropertyNode>> _properties;
public:
    ASTInterfacePropertyListNode(std::shared_ptr<ASTInterfaceStartNode> startNode, std::shared_ptr<ASTInterfaceEndNode> endNode);
    ASTInterfacePropertyListNode(std::shared_ptr<ASTInterfaceStartNode> startNode, std::vector<std::shared_ptr<ASTInterfacePropertyNode>> properties, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTInterfaceEndNode> endNode);
    std::vector<std::shared_ptr<ASTInterfacePropertyNode>> getProperties();
    uint64_t numProperties();
    std::shared_ptr<ASTInterfacePropertyListNode> addProperty(std::shared_ptr<ASTInterfacePropertyNode> property);
    std::shared_ptr<ASTInterfacePropertyListNode> addComma(std::shared_ptr<ASTCommaNode> comma);
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_INTERFACE_PROPERTY_LIST_NODE_H
