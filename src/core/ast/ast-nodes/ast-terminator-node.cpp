//
// Created by Johny Georges on 2024-02-09.
//

#include "ast-terminator-node.h"

ASTTerminatorNode::ASTTerminatorNode(Lexeme *lexeme) {
    _terminator = lexeme;
}

Lexeme* ASTTerminatorNode::getTerminator() {
    return _terminator;
}

ASTNodeType ASTTerminatorNode::getNodeType() {
    return AST_TERMINATOR_NODE;
}

std::string ASTTerminatorNode::toString() {
    return "TERMINATOR";
}

bool ASTTerminatorNode::isEqual(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTTerminatorNode*)other;
    return this->getTerminator()->isEqual(otherNode->getTerminator());
}