//
// Created by Johny Georges on 2024-05-25.
//

#include "function-declaration-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../type-checker.h"


namespace FunctionDeclarationTypeCheckerPolicy {
    TypeCheckerResult apply(ASTFunctionDeclarationNode* functionDeclarationNode, TypeCheckerRuleList* rules) {
        auto typeCheckerResult = TypeCheckerResult();
        auto functionTypeSignature = functionDeclarationNode->getTypeSignature();

        if (functionTypeSignature->getReturnType()->isUnknown()) {
            typeCheckerResult.addError(TypeCheckerErrorMessageTable::FunctionReturnTypeUnknown);
        } else if (functionTypeSignature->getReturnType()->isInvalid()) {
            typeCheckerResult.addError(TypeCheckerErrorMessageTable::FunctionReturnTypeInvalid);
        } else if (functionTypeSignature->getReturnType()->isVoid()) {
            typeCheckerResult.addError(TypeCheckerErrorMessageTable::FunctionReturnTypeVoid);
        }

        rules->addRule(new RequiredReturnExpressionTypeCheckerRule(functionTypeSignature->getReturnType()));
        typeCheckerResult.combine(TypeChecker::applyPolicyTo(functionDeclarationNode->getParameters(), rules));
        typeCheckerResult.combine(TypeChecker::applyPolicyTo(functionDeclarationNode->getBlock(), rules));

        return typeCheckerResult;
    }

}
