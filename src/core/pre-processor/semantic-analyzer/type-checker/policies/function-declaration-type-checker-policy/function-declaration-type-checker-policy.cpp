//
// Created by Johny Georges on 2024-05-25.
//

#include "function-declaration-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../type-checker.h"


namespace FunctionDeclarationTypeCheckerPolicy {
    void apply(ASTFunctionDeclarationNode* functionDeclarationNode, TypeCheckerResult* typeCheckerResult) {
        auto functionTypeSignature = functionDeclarationNode->getTypeSignature();

        TypeChecker::applyPolicyTo(functionDeclarationNode->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(functionDeclarationNode->getBlock(), typeCheckerResult);

        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            functionTypeSignature->getReturnType(),
            TypeCheckerErrorMessageTable::FunctionReturnTypeUnknown(
                functionDeclarationNode
            ),
            TypeCheckerErrorMessageTable::FunctionReturnTypeInvalid(
                functionDeclarationNode
            ),
            TypeCheckerErrorMessageTable::FunctionReturnTypeVoid(
                functionDeclarationNode
            ),
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getRequiredReturnExpressionTypeCheckerRule()->enforce(
            functionDeclarationNode->getBlock(),
            functionTypeSignature->getReturnType(),
            typeCheckerResult
        );
        TypeCheckerRuleProvider::getAllPathsReturnTypeCheckerRule()->enforce(
            functionDeclarationNode->getBlock(),
            TypeCheckerErrorMessageTable::FunctionNotAllPathsReturn(
                functionDeclarationNode
            ),
            typeCheckerResult
        );

    }

}
