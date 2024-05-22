//
// Created by Johny Georges on 2024-05-08.
//

#include "identifier-expression-type-signature-strategy.h"

void IdentifierExpressionTypeSignatureStrategy::assign(ASTIdentifierExpressionNode* identifierExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    identifierExpression->setTypeSignature(typeSignatureLookupTable->find(identifierExpression->getId()));
}