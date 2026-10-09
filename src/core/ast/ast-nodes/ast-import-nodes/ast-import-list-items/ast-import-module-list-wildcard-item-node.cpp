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

#include "ast-import-module-list-wildcard-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTImportModuleListWildcardItemNode::ASTImportModuleListWildcardItemNode(std::shared_ptr<Lexeme> lexeme) {
    _lexeme = lexeme;
}

std::shared_ptr<Lexeme> ASTImportModuleListWildcardItemNode::getLexeme() {
    return _lexeme;
}

std::shared_ptr<Position> ASTImportModuleListWildcardItemNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

std::shared_ptr<Position> ASTImportModuleListWildcardItemNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTImportModuleListWildcardItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_WILDCARD_ITEM_NODE;
}

std::string ASTImportModuleListWildcardItemNode::toString() {
    return "IMPORT_MODULE_LIST_WILDCARD_ITEM";
}

bool ASTImportModuleListWildcardItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportModuleListWildcardItemNode>(other);
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTImportModuleListWildcardItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log(this->toString(), "-", _lexeme->toString());
    Logger::log("----------");
}

std::string ASTImportModuleListWildcardItemNode::toSourceCode() {
    return _lexeme->getToken()->getSymbol()->toString();
}