//
// Created by Johny Georges on 2024-05-25.
//

#include "parameter-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ParameterTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTFunctionParameterNode> functionParameter, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ParameterTypeUnknown(functionParameter);
        auto invalidMessage = TypeCheckerErrorMessageTable::ParameterTypeInvalid(functionParameter);
        auto voidMessage = TypeCheckerErrorMessageTable::ParameterTypeVoid(functionParameter);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            functionParameter,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
    }
}