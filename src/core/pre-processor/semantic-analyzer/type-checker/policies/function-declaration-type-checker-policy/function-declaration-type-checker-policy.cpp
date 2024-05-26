//
// Created by Johny Georges on 2024-05-25.
//

#include "function-declaration-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../type-checker.h"


namespace FunctionDeclarationTypeCheckerPolicy {
    void apply(ASTFunctionDeclarationNode* functionDeclarationNode, TypeCheckerResult* typeCheckerResult) {
        auto functionTypeSignature = functionDeclarationNode->getTypeSignature();

        if (functionTypeSignature->getReturnType()->isUnknown()) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::FunctionReturnTypeUnknown);
        } else if (functionTypeSignature->getReturnType()->isInvalid()) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::FunctionReturnTypeInvalid);
        } else if (functionTypeSignature->getReturnType()->isVoid()) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::FunctionReturnTypeVoid);
        }

        TypeChecker::applyPolicyTo(functionDeclarationNode->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(functionDeclarationNode->getBlock(), typeCheckerResult);
        TypeChecker::typeCheckerRuleProvider
        .getRequiredReturnExpressionTypeCheckerRule()->enforce(
            functionDeclarationNode->getBlock(),
            functionTypeSignature->getReturnType(),
            typeCheckerResult
        );

    }

}
