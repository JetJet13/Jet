//
// Created by Johny Georges on 2024-04-30.
//

#include "type-signature-generator.h"
#include "types/literal-type-signature.h"
#include "types/literal-type-signature-factory.h"
#include "types/class-type-signature.h"

TypeSignatureGenerator::TypeSignatureGenerator(TokenTable* tokenTable) {
    _tokenTable = tokenTable;
}

TypeSignature* TypeSignatureGenerator::generateForLiteralExpression(ASTLiteralExpressionNode* literalExpression) {
    auto symbol = literalExpression->getLiteralNode()->getLiteral()->getToken()->getSymbol();
    if (symbol->isIntType()) {
        return LiteralTypeSignatureFactory::createIntLiteralType();
    } else if (symbol->isFloatType()) {
        return LiteralTypeSignatureFactory::createFloatLiteralType();
    } else if (symbol->isCharType()) {
        return LiteralTypeSignatureFactory::createCharLiteralType();
    } else if (symbol->isStringType()) {
        return LiteralTypeSignatureFactory::createStringLiteralType();
    } else if (symbol->isBooleanType()) {
        return LiteralTypeSignatureFactory::createBooleanLiteralType();
    } else {
        return LiteralTypeSignatureFactory::createNotNullLiteralType();
    }
}

TypeSignature* TypeSignatureGenerator::generateForClassPropertyAccessExpression(ASTClassPropertyAccessExpressionNode* classPropertyAccessExpressionNode) {
    return new
}

TypeSignature* TypeSignatureGenerator::generateForThisExpression(ASTThisExpressionNode* thisExpression) {
    return new ClassTypeSignature(thisExpression->getThisNode()->getLexeme());
}