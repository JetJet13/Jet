//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_UNARY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_UNARY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../type-signature-strategy-provider.h"

class UnaryExpressionTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTUnaryExpressionNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_UNARY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
