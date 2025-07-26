//
// Created by Johny Georges on 2024-05-25.
//

#include "function-declaration-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../../jet-utils-type-signature-map/jet-utils-type-signature-map.h"

namespace FunctionDeclarationTypeCheckerPolicy {
    void apply(ASTFunctionDeclarationNode* functionDeclarationNode, TypeCheckerResult* typeCheckerResult) {
        auto functionTypeSignature = functionDeclarationNode->getTypeSignature();

        TypeChecker::applyPolicyTo(functionDeclarationNode->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(functionDeclarationNode->getBlock(), typeCheckerResult);
        auto unknownMessage = TypeCheckerErrorMessageTable::FunctionReturnTypeUnknown(functionDeclarationNode->getDefinition());
        auto invalidMessage = TypeCheckerErrorMessageTable::FunctionReturnTypeInvalid(functionDeclarationNode->getDefinition());
        auto voidMessage = TypeCheckerErrorMessageTable::FunctionReturnTypeVoid(functionDeclarationNode->getDefinition());
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
        auto notAllPathsReturnMessage = TypeCheckerErrorMessageTable::FunctionNotAllPathsReturn(functionDeclarationNode->getDefinition());
        TypeCheckerRuleProvider::getAllPathsReturnTypeCheckerRule()->enforce(
            functionDeclarationNode->getBlock(),
            notAllPathsReturnMessage,
            typeCheckerResult
        );

        if (JetUtilsTypeSignatureMap::doesIdConflict(functionDeclarationNode->getName()->getId())){
            typeCheckerResult->addError(
                TypeCheckerErrorMessageTable::FunctionNameConflictsWithBuiltInFunctionName(functionDeclarationNode->getDefinition())()
            );
        }

    }

}
