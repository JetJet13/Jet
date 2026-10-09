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

#include "ast-import-path-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportPathNode::ASTImportPathNode(std::shared_ptr<ASTStringLiteralNode> importPath) {
    _importPath = importPath;
    _children.push_back(_importPath);
}

std::shared_ptr<ASTStringLiteralNode> ASTImportPathNode::getImportPath() {
    return _importPath;
}

std::shared_ptr<Position> ASTImportPathNode::getStartPosition() {
    return _importPath->getStartPosition();
}

std::shared_ptr<Position> ASTImportPathNode::getEndPosition() {
    return _importPath->getEndPosition();
}

ASTNodeType ASTImportPathNode::getNodeType() {
    return AST_IMPORT_PATH_NODE;
}

std::string ASTImportPathNode::toString() {
    return "IMPORT_PATH";
}

bool ASTImportPathNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportPathNode>(other);
    return this->getImportPath()->isSameAs(otherNode->getImportPath());
}

void ASTImportPathNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _importPath->print();
    Logger::log("----------");
}

std::string ASTImportPathNode::toSourceCode() {
    return _importPath->toSourceCode();
}