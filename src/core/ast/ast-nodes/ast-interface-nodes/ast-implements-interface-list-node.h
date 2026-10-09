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
// Created by Johny Georges on 2025-07-05.
//

#ifndef JETLANG_AST_IMPLEMENTS_INTERFACE_LIST_NODE_H
#define JETLANG_AST_IMPLEMENTS_INTERFACE_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-interface-start-node.h"
#include "ast-interface-end-node.h"
#include "ast-interface-property-node.h"
#include "ast-implements-node.h"
#include "ast-implements-interface-name-node.h"
#include "../ast-comma-node.h"

class ASTImplementsInterfaceListNode : public ASTNode {
private:
    std::shared_ptr<ASTImplementsNode> _implements;
    std::vector<std::shared_ptr<ASTCommaNode>> _commas;
    std::vector<std::shared_ptr<ASTImplementsInterfaceNameNode>> _interfaceNames;
public:
    ASTImplementsInterfaceListNode(std::shared_ptr<ASTImplementsNode> implementsKeyword);
    ASTImplementsInterfaceListNode(std::shared_ptr<ASTImplementsNode> implementsKeyword, std::vector<std::shared_ptr<ASTImplementsInterfaceNameNode>> interfaceNames, std::vector<std::shared_ptr<ASTCommaNode>> commas);
    std::vector<std::shared_ptr<ASTImplementsInterfaceNameNode>> getInterfaceNames();
    uint64_t numInterfaces();
    std::shared_ptr<ASTImplementsInterfaceListNode> addInterface(std::shared_ptr<ASTImplementsInterfaceNameNode> interfaceName);
    std::shared_ptr<ASTImplementsInterfaceListNode> addComma(std::shared_ptr<ASTCommaNode> comma);
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPLEMENTS_INTERFACE_LIST_NODE_H
