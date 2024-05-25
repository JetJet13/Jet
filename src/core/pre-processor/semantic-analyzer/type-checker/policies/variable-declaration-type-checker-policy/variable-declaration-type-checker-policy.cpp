//
// Created by Johny Georges on 2024-05-21.
//

#include "variable-declaration-type-checker-policy.h"
#include "../../types/type-checker-result-factory.h"
#include "../../types/type-checker-error-message-table.h"

namespace VariableDeclarationTypeCheckerPolicy {
    TypeCheckerResult apply(ASTVariableDeclarationNode* variableDeclarationNode, TypeCheckerRuleList* rules) {
        auto varTypeSignature = variableDeclarationNode->getTypeSignature();
        auto initializerTypeSignature = variableDeclarationNode->getInitializerNode()->getTypeSignature();
        if (varTypeSignature->isEqualTo(initializerTypeSignature)) {
            return TypeCheckerResultFactory::createOkResult();
        } else if (varTypeSignature->isUnknown()) {
            return TypeCheckerResultFactory::createErrorResult({
                   TypeCheckerErrorMessageTable::VariableTypeUnknown
           });
        } else if (varTypeSignature->isInvalid()) {
            return TypeCheckerResultFactory::createErrorResult({
                   TypeCheckerErrorMessageTable::VariableTypeInvalid
           });
        } else if (varTypeSignature->isVoid()) {
            return TypeCheckerResultFactory::createErrorResult({
                   TypeCheckerErrorMessageTable::VariableTypeVoid
           });
        } else {
            return TypeCheckerResultFactory::createErrorResult({
                   TypeCheckerErrorMessageTable::VariableTypeMismatch
           });
        }
    }
}
