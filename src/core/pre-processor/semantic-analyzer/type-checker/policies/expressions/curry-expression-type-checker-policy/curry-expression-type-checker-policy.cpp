//
// Created by Johny Georges on 2024-05-29.
//

#include "curry-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../../../../type-signature/function-type-signature/function-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"

namespace CurryExpressionTypeCheckerPolicy {
    void apply(ASTCurryExpressionNode* curryExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
        ->enforce(
            curryExpression->getTypeSignature(),
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown,
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid,
            typeCheckerResult
        );

        auto callableTypeSignature = curryExpression->getCallableExpression()->getTypeSignature();
        if (callableTypeSignature->is(FUNCTION_TYPE_SOURCE)) {
            auto parameterList = ((FunctionTypeSignature*)callableTypeSignature)->getParameterList();
            TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
            ->enforce(
                parameterList->numParameters(),
                curryExpression->numArguments(),
                TypeCheckerErrorMessageTable::CurryCallNotEnoughArguments,
                TypeCheckerErrorMessageTable::CurryCallTooManyArguments,
                typeCheckerResult
            );

            TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                parameterList,
                curryExpression->getArguments(),
                TypeCheckerErrorMessageTable::CurryCallArgumentTypeMismatch,
                typeCheckerResult
            );

        } else if (callableTypeSignature->is(CLASS_METHOD_TYPE_SOURCE)) {
            auto parameterList = ((ClassMethodTypeSignature*)callableTypeSignature)->getParameters();
            TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
            ->enforce(
                parameterList->numParameters(),
                curryExpression->numArguments(),
                TypeCheckerErrorMessageTable::CurryCallNotEnoughArguments,
                TypeCheckerErrorMessageTable::CurryCallTooManyArguments,
                typeCheckerResult
            );

            TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                parameterList,
                curryExpression->getArguments(),
                TypeCheckerErrorMessageTable::CurryCallArgumentTypeMismatch,
                typeCheckerResult
            );
        } else {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::NotCallableCurryType);
        }

    }
}