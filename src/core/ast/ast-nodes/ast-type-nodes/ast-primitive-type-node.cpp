//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-primitive-type-node.h"

ASTPrimitiveTypeNode::ASTPrimitiveTypeNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTPrimitiveTypeNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTPrimitiveTypeNode::getNodeType() {
    return AST_PRIMITIVE_TYPE_NODE;
}

std::string ASTPrimitiveTypeNode::toString() {
    return "PRIMITIVE_TYPE";
}

bool ASTPrimitiveTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTPrimitiveTypeNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}
