//
// Created by Johny Georges on 2024-05-08.
//

#include "identifier-expression-type-signature-strategy.h"

TypeSignature* IdentifierExpressionTypeSignatureStrategy::create(ASTIdentifierExpressionNode* identifierExpression, TypeSignatureLookupTable* typeSignatureLookupTable, TokenTable* tokenTable) {
    return typeSignatureLookupTable->find(
        tokenTable->getIdentifier(
                identifierExpression
                ->getIdentifierNode()
                ->getIdentifier()
                ->getToken()
                ->getValueId()
                .value()
        ).value()
    );
}