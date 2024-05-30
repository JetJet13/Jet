//
// Created by Johny Georges on 2024-05-25.
//

#include "parameter-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ParameterTypeCheckerPolicy {
    void apply(ASTFunctionParameterNode* functionParameter, TypeCheckerResult* typeCheckerResult) {

        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
                functionParameter,
                TypeCheckerErrorMessageTable::ParameterTypeUnknown(
                    functionParameter->getIdentifier()->getIdentifierNode()->getLexeme()
                ),
                TypeCheckerErrorMessageTable::ParameterTypeInvalid(
                    functionParameter->getIdentifier()->getIdentifierNode()->getLexeme()
                ),
                TypeCheckerErrorMessageTable::ParameterTypeVoid(
                    functionParameter->getIdentifier()->getIdentifierNode()->getLexeme()
                ),
                typeCheckerResult
        );
    }
};