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

#include "ast-implements-interface-name-last-node.h"

std::shared_ptr<ASTImplementsInterfaceNameNode> ASTImplementsInterfaceNameLastNode::convertToInterfaceName() {
    auto node = std::make_shared<ASTImplementsInterfaceNameNode>(this->getLexeme());
    node->setId(this->getId());
    return node;
}

ASTNodeType ASTImplementsInterfaceNameLastNode::getNodeType() {
    return AST_IMPLEMENTS_INTERFACE_NAME_LAST_NODE;
}

std::string ASTImplementsInterfaceNameLastNode::toString() {
    return "IMPLEMENTS_INTERFACE_NAME_LAST";
}

std::string ASTImplementsInterfaceNameLastNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}