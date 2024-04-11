//
// Created by Johny Georges on 2024-04-11.
//

#include "ast-int-literal-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTIntLiteralTypeNode::ASTIntLiteralTypeNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTIntLiteralTypeNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTIntLiteralTypeNode::getNodeType() {
    return AST_INT_LITERAL_TYPE_NODE;
}

std::string ASTIntLiteralTypeNode::toString() {
    return "INT_LITERAL_TYPE";
}

bool ASTIntLiteralTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTIntLiteralTypeNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTIntLiteralTypeNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}