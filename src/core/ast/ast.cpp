//
// Created by Johny Georges on 2024-01-12.
//

#include "ast.h"

AST::AST() {
    _children = {};
}

void AST::addChild(ASTNode* node) {
    _children.push_back(node);
}

std::vector<ASTNode*> AST::getChildren() {
    return _children;
}