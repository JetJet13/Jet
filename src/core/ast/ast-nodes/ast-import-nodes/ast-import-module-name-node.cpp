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
// Created by Johny Georges on 2024-04-13.
//

#include "ast-import-module-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportModuleNameNode::ASTImportModuleNameNode(std::shared_ptr<ASTIdentifierNode> identifier) {
    _identifier = identifier;
    _children.push_back(_identifier);
}

std::shared_ptr<ASTIdentifierNode> ASTImportModuleNameNode::getIdentifier() {
    return _identifier;
}

std::shared_ptr<Position> ASTImportModuleNameNode::getStartPosition() {
    return _identifier->getStartPosition();
}

std::shared_ptr<Position> ASTImportModuleNameNode::getEndPosition() {
    return _identifier->getEndPosition();
}

ASTNodeType ASTImportModuleNameNode::getNodeType() {
    return AST_IMPORT_MODULE_NAME_NODE;
}

std::string ASTImportModuleNameNode::toString() {
    return "IMPORT_MODULE_NAME";
}

bool ASTImportModuleNameNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportModuleNameNode>(other);
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTImportModuleNameNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}

std::string ASTImportModuleNameNode::toSourceCode() {
    return _identifier->toSourceCode();
}