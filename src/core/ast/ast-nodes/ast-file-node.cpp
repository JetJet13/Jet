//
// Created by Johny Georges on 2024-01-15.
//

#include "ast-file-node.h"
#include "../types/source-code-builder/source-code-builder.h"

ASTFileNode::ASTFileNode(std::vector<ASTNode*> body) {
    _body = body;
}

void ASTFileNode::append(ASTNode *node) {
    _body.push_back(node);
}

std::vector<ASTNode*>* ASTFileNode::getBody() {
    return &_body;
}

Position* ASTFileNode::getStartPosition() {
    if (_body.empty()) {
        return new Position();
    }
    return _body[0]->getStartPosition();
}

Position* ASTFileNode::getEndPosition() {
    if (_body.empty()) {
        return new Position();
    }
    return _body[_body.size() - 1]->getEndPosition();
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
    for (int i = 0; i < _body.size(); ++i) {
        if (!_body[i]->isSameAs(otherNode->getBody()->at(i))) {
            return false;
        }
    }
    return true;
}

std::string ASTFileNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    for (auto node : _body) {
        sourceCodeBuilder.addWithNewLine(node);
    }
    return sourceCodeBuilder.build();
}