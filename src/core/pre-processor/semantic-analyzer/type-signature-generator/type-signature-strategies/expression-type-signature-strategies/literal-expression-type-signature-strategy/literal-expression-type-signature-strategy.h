//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_LITERAL_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_LITERAL_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../type-signature-strategy-provider.h"

class LiteralExpressionTypeSignatureStrategy {
public:
    TypeSignature* create(ASTLiteralExpressionNode* literalExpression, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_LITERAL_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
