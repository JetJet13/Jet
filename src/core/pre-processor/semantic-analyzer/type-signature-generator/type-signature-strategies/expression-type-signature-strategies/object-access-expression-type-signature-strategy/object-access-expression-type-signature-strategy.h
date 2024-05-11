//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_OBJECT_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../type-signature-strategy-provider.h"

class ObjectAccessExpressionTypeSignatureStrategy {
public:
    TypeSignature* create(ASTObjectAccessExpressionNode* objectAccessExpression, TokenTable* tokenTable, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_OBJECT_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
