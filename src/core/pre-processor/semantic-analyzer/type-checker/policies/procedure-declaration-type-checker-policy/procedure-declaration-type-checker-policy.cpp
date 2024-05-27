//
// Created by Johny Georges on 2024-05-25.
//

#include "procedure-declaration-type-checker-policy.h"
#include "../../type-checker.h"

namespace ProcedureDeclarationTypeCheckerPolicy {
    void apply(ASTProcedureDeclarationNode* procedureDeclarationNode, TypeCheckerResult* typeCheckerResult) {
        TypeChecker::applyPolicyTo(procedureDeclarationNode->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(procedureDeclarationNode->getBlock(), typeCheckerResult);
        TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule()->enforce(
            procedureDeclarationNode->getBlock(),
            typeCheckerResult
        );
    }
}