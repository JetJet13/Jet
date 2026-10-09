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

#include "ast-package-path-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTPackagePathNode::ASTPackagePathNode(std::shared_ptr<ASTStringLiteralNode> packagePath) {
    _packagePath = packagePath;
    _children.push_back(_packagePath);
}

std::shared_ptr<ASTStringLiteralNode> ASTPackagePathNode::getPackagePath() {
    return _packagePath;
}

std::shared_ptr<Position> ASTPackagePathNode::getStartPosition() {
    return _packagePath->getStartPosition();
}

std::shared_ptr<Position> ASTPackagePathNode::getEndPosition() {
    return _packagePath->getEndPosition();
}

ASTNodeType ASTPackagePathNode::getNodeType() {
    return AST_PACKAGE_PATH_NODE;
}

std::string ASTPackagePathNode::toString() {
    return "PACKAGE_PATH";
}

bool ASTPackagePathNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTPackagePathNode>(other);
    return this->getPackagePath()->isSameAs(otherNode->getPackagePath());
}

void ASTPackagePathNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _packagePath->print();
    Logger::log("----------");
}

std::string ASTPackagePathNode::toSourceCode() {
    return _packagePath->toSourceCode();
}