//
// Created by Johny Georges on 2024-01-15.
//

#include "ast-file-node.h"

ASTFileNode::ASTFileNode() {
    _body = {};
}

void ASTFileNode::append(ASTNode *node) {
    _body.push_back(node);
}

void ASTFileNode::prepend(ASTNode *node) {
    _body.insert(_body.begin(), node);
}

ASTNodeType ASTFileNode::getNodeType() {
    return AST_FILE_NODE;
}