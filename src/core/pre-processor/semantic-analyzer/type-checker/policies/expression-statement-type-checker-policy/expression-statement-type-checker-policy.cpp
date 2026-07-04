//
// Created by Johny Georges on 2024-05-28.
//

#include "expression-statement-type-checker-policy.h"
#include "../../type-checker.h"

namespace ExpressionStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTExpressionStatementNode> expressionStatementNode, TypeCheckerResult* typeCheckerResult) {
        TypeChecker::applyPolicyTo(expressionStatementNode->getExpression(), typeCheckerResult);
    }
}