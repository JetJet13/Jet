//
// Created by Johny Georges on 2024-05-25.
//

#include "function-block-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../types/type-checker-error-message-table.h"

namespace FunctionBlockTypeCheckerPolicy {
    TypeCheckerResult apply(ASTFunctionBlockNode* functionBlockNode, TypeCheckerRuleList* rules) {
        auto typeCheckerResult = TypeCheckerResult();

        auto noReturnExpressionRule = rules->findNoReturnExpressionRule();
        auto requiredReturnExpressionRule = rules->findRequiredReturnExpressionRule();
        auto statementRules = new TypeCheckerRuleList(rules);

        auto hasReturnExpression = functionBlockNode->hasReturnExpression();
        if (requiredReturnExpressionRule && hasReturnExpression) {
            statementRules->replaceRule(
                requiredReturnExpressionRule.value(),
                requiredReturnExpressionRule.value()->convertToOptional()
            );
        }

        for (auto statement : *functionBlockNode->getContents()) {

            if (statement->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
                auto returnExpression = (ASTFunctionReturnExpressionNode*)statement;

                if (requiredReturnExpressionRule &&
                    !returnExpression->getTypeSignature()->isEqualTo(requiredReturnExpressionRule.value()->getReturnType())) {
                    typeCheckerResult.addError(TypeCheckerErrorMessageTable::FunctionReturnExpressionMismatch);
                }

                if (noReturnExpressionRule) {
                    typeCheckerResult.addError(TypeCheckerErrorMessageTable::ProcedureHasReturnExpression);
                }
            }

            typeCheckerResult.combine(TypeChecker::applyPolicyTo(statement, statementRules));
        }

        return typeCheckerResult;
    }

}