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
        auto unknownMessage = TypeCheckerErrorMessageTable::FunctionReturnTypeUnknown(functionDeclarationNode);
        auto invalidMessage = TypeCheckerErrorMessageTable::FunctionReturnTypeInvalid(functionDeclarationNode);
        auto voidMessage = TypeCheckerErrorMessageTable::FunctionReturnTypeVoid(functionDeclarationNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            functionTypeSignature->getReturnType(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
        TypeCheckerRuleProvider::getRequiredReturnExpressionTypeCheckerRule()->enforce(
            functionDeclarationNode->getBlock(),
            functionTypeSignature->getReturnType(),
            typeCheckerResult
        );
        auto notAllPathsReturnMessage = TypeCheckerErrorMessageTable::FunctionNotAllPathsReturn(functionDeclarationNode);
        TypeCheckerRuleProvider::getAllPathsReturnTypeCheckerRule()->enforce(
            functionDeclarationNode->getBlock(),
            notAllPathsReturnMessage,
            typeCheckerResult
        );

    }

}
