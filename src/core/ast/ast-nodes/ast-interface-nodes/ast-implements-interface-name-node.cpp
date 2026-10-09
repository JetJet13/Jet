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

#include "ast-implements-interface-name-node.h"

ASTNodeType ASTImplementsInterfaceNameNode::getNodeType() {
    return AST_IMPLEMENTS_INTERFACE_NAME_NODE;
}

std::string ASTImplementsInterfaceNameNode::toString() {
    return "IMPLEMENTS_INTERFACE_NAME";
}

std::string ASTImplementsInterfaceNameNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}