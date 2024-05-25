//
// Created by Johny Georges on 2024-05-25.
//

#include "procedure-declaration-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../type-checker.h"

namespace ProcedureDeclarationTypeCheckerPolicy {
    TypeCheckerResult apply(ASTProcedureDeclarationNode* procedureDeclarationNode, TypeCheckerRuleList* rules) {
        auto typeCheckerResult = TypeCheckerResult();

        rules->addRule(new NoReturnExpressionTypeCheckerRule());
        typeCheckerResult.combine(TypeChecker::applyPolicyTo(procedureDeclarationNode->getParameters(), rules));
        typeCheckerResult.combine(TypeChecker::applyPolicyTo(procedureDeclarationNode->getBlock(), rules));

        return typeCheckerResult;
    }
}