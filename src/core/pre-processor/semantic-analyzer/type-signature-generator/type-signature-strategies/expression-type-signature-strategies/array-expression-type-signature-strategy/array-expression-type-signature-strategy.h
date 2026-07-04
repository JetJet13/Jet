//
// Created by Johny Georges on 2024-05-07.
//

#ifndef JETLANG_ARRAY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_ARRAY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../type-signature-strategy-provider.h"

class ArrayExpressionTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTArrayExpressionNode> arrayExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_ARRAY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
