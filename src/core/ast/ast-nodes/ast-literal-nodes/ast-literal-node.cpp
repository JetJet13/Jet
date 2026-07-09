//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-literal-node.h"

ASTLiteralNode::ASTLiteralNode(std::shared_ptr<Lexeme> lexemeLiteral) {
    _lexeme = lexemeLiteral;
}

std::shared_ptr<Lexeme> ASTLiteralNode::getLiteral() {
    return _lexeme;
}

void ASTLiteralNode::setTypeSignature(std::shared_ptr<LiteralTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<LiteralTypeSignature> ASTLiteralNode::getLiteralTypeSignature() {
    return std::dynamic_pointer_cast<LiteralTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTLiteralNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTLiteralNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

std::shared_ptr<Position> ASTLiteralNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTLiteralNode::getNodeType() {
    return AST_LITERAL_NODE;
}

std::string ASTLiteralNode::toString() {
    return "LITERAL";
}


bool ASTLiteralNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTLiteralNode>(other);
    return this->getLiteral()->hasSameSymbolTypeAs(otherNode->getLiteral());
}

std::string ASTLiteralNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}