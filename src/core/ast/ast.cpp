//
// Created by Johny Georges on 2024-01-12.
//

#include "ast.h"

AST::AST() {
    _children = {};
}

void AST::addChild(std::shared_ptr<ASTNode> node) {
    _children.push_back(node);
}

std::vector<std::shared_ptr<ASTNode>> AST::getChildren() {
    return _children;
}