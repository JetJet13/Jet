//
// Created by Johny Georges on 2024-05-08.
//

#ifndef JETLANG_IDENTIFIER_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_IDENTIFIER_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../type-signature/type-signature.h"
#include "../../../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "../../../../../type-signature-lookup-table/type-signature-lookup-table.h"

class IdentifierExpressionTypeSignatureStrategy {
public:
    TypeSignature* create(ASTIdentifierExpressionNode* identifierExpression, TypeSignatureLookupTable* typeSignatureLookupTable);
};

#endif //JETLANG_IDENTIFIER_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
