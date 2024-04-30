//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-primitive-type-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "types/literal-type-factory.h"

ASTPrimitiveTypeNode::ASTPrimitiveTypeNode(Lexeme *lexeme) {
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

void ASTPrimitiveTypeNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}

BaseType* ASTPrimitiveTypeNode::getType() {
    auto symbol = _lexeme->getToken()->getSymbol();
    if (symbol->isIntType()) {
        return LiteralTypeFactory::createIntLiteralType();
    } else if (symbol->isFloatType()) {
        return LiteralTypeFactory::createFloatLiteralType();
    } else if (symbol->isCharType()) {
        return LiteralTypeFactory::createCharLiteralType();
    } else if (symbol->isStringType()) {
        return LiteralTypeFactory::createStringLiteralType();
    } else if (symbol->isBooleanType()) {
        return LiteralTypeFactory::createBooleanLiteralType();
    } else {
        return LiteralTypeFactory::createNotNullLiteralType();
    }
}