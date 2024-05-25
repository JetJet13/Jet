//
// Created by Johny Georges on 2024-05-25.
//

#include "parameter-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"

namespace ParameterTypeCheckerPolicy {
    TypeCheckerResult apply(ASTFunctionParameterNode* functionParameter, TypeCheckerRuleList* rules) {
        auto typeCheckerResult = TypeCheckerResult();
        if (functionParameter->getTypeSignature()->isUnknown()) {
            typeCheckerResult.addError(TypeCheckerErrorMessageTable::ParameterTypeUnknown);
        } else if (functionParameter->getTypeSignature()->isInvalid()) {
            typeCheckerResult.addError(TypeCheckerErrorMessageTable::ParameterTypeInvalid);
        } else if (functionParameter->getTypeSignature()->isVoid()) {
            typeCheckerResult.addError(TypeCheckerErrorMessageTable::ParameterTypeVoid);
        }
        return typeCheckerResult;
    }
};