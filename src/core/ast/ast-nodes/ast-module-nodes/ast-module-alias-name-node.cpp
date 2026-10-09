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
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-alias-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleAliasNameNode::ASTModuleAliasNameNode(std::shared_ptr<ASTIdentifierNode> identifier) {
    _identifier = identifier;
    _children.push_back(_identifier);
}

std::shared_ptr<ASTIdentifierNode> ASTModuleAliasNameNode::getIdentifier() {
    return _identifier;
}

std::shared_ptr<Position> ASTModuleAliasNameNode::getStartPosition() {
    return _identifier->getStartPosition();
}

std::shared_ptr<Position> ASTModuleAliasNameNode::getEndPosition() {
    return _identifier->getEndPosition();
}

ASTNodeType ASTModuleAliasNameNode::getNodeType() {
    return AST_MODULE_ALIAS_NAME_NODE;
}

std::string ASTModuleAliasNameNode::toString() {
    return "MODULE_ALIAS_NAME";
}

bool ASTModuleAliasNameNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleAliasNameNode>(other);
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTModuleAliasNameNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}

std::string ASTModuleAliasNameNode::toSourceCode() {
    return _identifier->toSourceCode();
}