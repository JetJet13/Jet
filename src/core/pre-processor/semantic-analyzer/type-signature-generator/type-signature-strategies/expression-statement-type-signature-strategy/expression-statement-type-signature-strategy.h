//
// Created by Johny Georges on 2024-05-23.
//

#ifndef JETLANG_EXPRESSION_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_EXPRESSION_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-expression-statement-node.h"

class ExpressionStatementTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTExpressionStatementNode> expressionStatementNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};


#endif //JETLANG_EXPRESSION_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
