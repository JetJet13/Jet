//
// Created by Johny Georges on 2024-01-15.
//

#include "ast-file-node.h"

ASTFileNode::ASTFileNode(ASTBlockNode* body) {
    _body = body;
}

void ASTFileNode::append(ASTNode *node) {
    _body->addContent(node);
}

ASTBlockNode* ASTFileNode::getBody() {
    return _body;
}

ASTNodeType ASTFileNode::getNodeType() {
    return AST_FILE_NODE;
}

std::string ASTFileNode::toString() {
    return "FILE";
}

bool ASTFileNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFileNode*)other;
    return _body->isSameAs(otherNode->getBody());
}