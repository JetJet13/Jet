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

std::vector<ASTNode*> ASTFileNode::getBody() {
    return _body;
}

ASTNodeType ASTFileNode::getNodeType() {
    return AST_FILE_NODE;
}

std::string ASTFileNode::toString() {
    return "FILE";
}

bool ASTFileNode::isEqual(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFileNode*)other;
    for (int i = 0; i < _body.size(); ++i) {
        if (!_body[i]->isEqual(otherNode->getBody()[i])) {
            return false;
        }
    }
    return true;
}