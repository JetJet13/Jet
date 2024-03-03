//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-literal-node.h"

ASTLiteralNode::ASTLiteralNode(Lexeme* lexemeLiteral) {
    _lexemeLiteral = lexemeLiteral;
}

Lexeme* ASTLiteralNode::getLiteral() {
    return _lexemeLiteral;
}

ASTNodeType ASTLiteralNode::getNodeType() {
    return AST_LITERAL_NODE;
}

std::string ASTLiteralNode::toString() {
    return "LITERAL";
}

bool ASTLiteralNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTLiteralNode*)other;
    return this->getLiteral()->hasSameSymbolTypeAs(otherNode->getLiteral());
}