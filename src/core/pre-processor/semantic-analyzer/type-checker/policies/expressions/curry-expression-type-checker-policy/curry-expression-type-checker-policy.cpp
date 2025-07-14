//
// Created by Johny Georges on 2024-05-29.
//

#include "curry-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../../../../type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"
#include "../../../../../../type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"

namespace CurryExpressionTypeCheckerPolicy {
    void apply(ASTCurryExpressionNode* curryExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(curryExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(curryExpression);
        TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
        ->enforce(
            curryExpression->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            typeCheckerResult
        );

        auto callableTypeSignature = curryExpression->getCallableExpression()->getTypeSignature();
        if (callableTypeSignature->typeTargetIs(FUNCTION_TYPE_SOURCE)) {
            auto parameterList = ((FunctionTypeSignature*)callableTypeSignature)->getParameterList();
            auto notEnoughArgumentsMessage = TypeCheckerErrorMessageTable::CurryCallNotEnoughArguments(curryExpression);
            auto tooManyArgumentsMessage = TypeCheckerErrorMessageTable::CurryCallTooManyArguments(curryExpression);
            TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
            ->enforce(
                parameterList->numParameters(),
                curryExpression->numArguments(),
                notEnoughArgumentsMessage,
                tooManyArgumentsMessage,
                typeCheckerResult
            );

            auto argumentTypeMismatchMessage = TypeCheckerErrorMessageTable::CurryCallArgumentTypeMismatch(curryExpression);
            TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                parameterList->getParameterTypes(),
                curryExpression->getArguments(),
                argumentTypeMismatchMessage,
                typeCheckerResult
            );

        } else if (callableTypeSignature->typeTargetIs(CLASS_METHOD_TYPE_SOURCE)) {
            auto parameterList = ((ClassMethodTypeSignature*)callableTypeSignature)->getParameters();
            auto notEnoughArgumentsMessage = TypeCheckerErrorMessageTable::CurryCallNotEnoughArguments(curryExpression);
            auto tooManyArgumentsMessage = TypeCheckerErrorMessageTable::CurryCallTooManyArguments(curryExpression);
            TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
            ->enforce(
                parameterList->numParameters(),
                curryExpression->numArguments(),
                notEnoughArgumentsMessage,
                tooManyArgumentsMessage,
                typeCheckerResult
            );

            auto argumentTypeMismatch = TypeCheckerErrorMessageTable::CurryCallArgumentTypeMismatch(curryExpression);
            TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                parameterList->getParameterTypes(),
                curryExpression->getArguments(),
                argumentTypeMismatch,
                typeCheckerResult
            );
        } else {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::NotCallableCurryType(curryExpression)());
        }

    }
}