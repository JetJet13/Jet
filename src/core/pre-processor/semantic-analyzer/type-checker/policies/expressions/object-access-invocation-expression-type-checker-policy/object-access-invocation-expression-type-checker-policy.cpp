// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"

namespace ObjectAccessInvocationExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> objectAccessInvocationExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto objectAccessExpression = objectAccessInvocationExpression->getObjectAccess();
        auto sourceTypeSignature = objectAccessExpression->getSource()->getSource()->getTypeSignature();
        if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
            sourceTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature)->getUnderlyingType());
        }

        if (sourceTypeSignature->typeTargetIs(CLASS_INSTANCE_TYPE_SOURCE)) {
            auto classInstanceSource = std::dynamic_pointer_cast<ClassInstanceTypeSignature>(sourceTypeSignature);
            auto methodName = objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
            auto methodId = FunctionIdGenerator::generateFor(methodName, objectAccessInvocationExpression->getArguments()->getArgumentListTypeSignature()->toDetailString());
            auto id = classInstanceSource->getClass()->addClassNameToKey(methodId);
            auto classMethod = classInstanceSource->getClass()->getInstanceMethods()->find(id);

            if (!fileScope->isClassScope() && classMethod && classMethod.value()->getAccessModifier()->isPrivate()) {
                auto classMethodIsPrivateMessage = TypeCheckerErrorMessageTable::ClassMethodIsPrivate(objectAccessInvocationExpression);
                typeCheckerResult->addError(classMethodIsPrivateMessage());
            }

        } else if (sourceTypeSignature->typeTargetIs(CLASS_TYPE_SOURCE)) {
            auto classSource = std::dynamic_pointer_cast<ClassTypeSignature>(sourceTypeSignature);
            auto methodName = objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
            auto methodId = FunctionIdGenerator::generateFor(methodName, objectAccessInvocationExpression->getArguments()->getArgumentListTypeSignature()->toDetailString());
            auto id = classSource->addClassNameToKey(methodId);
            auto classStaticMethod = classSource->getStaticMethods()->find(id);

            if (!fileScope->isClassScope() && classStaticMethod && classStaticMethod.value()->getAccessModifier()->isPrivate()) {
                auto classMethodIsPrivateMessage = TypeCheckerErrorMessageTable::ClassMethodIsPrivate(objectAccessInvocationExpression);
                typeCheckerResult->addError(classMethodIsPrivateMessage());
            }
        }

        TypeChecker::applyPolicyTo(objectAccessInvocationExpression->getSource()->getSource(), typeCheckerResult, fileScope);
        TypeChecker::applyPolicyTo(objectAccessInvocationExpression->getArguments(), typeCheckerResult, fileScope);
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(objectAccessInvocationExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(objectAccessInvocationExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
                objectAccessInvocationExpression,
                unknownMessage,
                invalidMessage,
                typeCheckerResult
        );
        auto notInvocableMessage = TypeCheckerErrorMessageTable::NotInvocable(objectAccessInvocationExpression->getObjectAccess());
        TypeCheckerRuleProvider::getInvocableTypeSignatureTypeCheckerRule()
        ->enforce(
                objectAccessInvocationExpression->getObjectAccess()->getTypeSignature(),
                notInvocableMessage,
                typeCheckerResult
        );

        if (!objectAccessInvocationExpression->getObjectAccess()->getTypeSignature()->isInvocable()) {
            return;
        }

        auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(objectAccessInvocationExpression->getObjectAccess()->getTypeSignature());
        auto notEnoughArguments = TypeCheckerErrorMessageTable::FunctionCallNotEnoughArguments(objectAccessInvocationExpression);
        auto tooManyArguments = TypeCheckerErrorMessageTable::FunctionCallTooManyArguments(objectAccessInvocationExpression);
        auto argumentListCountResultOk = TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
                                         ->enforce(
                                            invocableTypeSignature->getParameterTypes()->size(),
                                            objectAccessInvocationExpression->getArguments()->numArguments(),
                                            invocableTypeSignature->hasVariableLengthParameters(),
                                            notEnoughArguments,
                                            tooManyArguments,
                                            typeCheckerResult
                                         );

        if (!argumentListCountResultOk) {
            return;
        }

        auto unknownReturnTypeMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(objectAccessInvocationExpression);
        auto invalidReturnTypeMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(objectAccessInvocationExpression);
        TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
        ->enforce(
            invocableTypeSignature->getReturnType(),
            unknownReturnTypeMessage,
            invalidReturnTypeMessage,
            typeCheckerResult
        );

        auto argumentTypeMismatch = TypeCheckerErrorMessageTable::FunctionCallArgumentTypeMismatch(objectAccessInvocationExpression);
        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            invocableTypeSignature->getParameterTypes(),
            objectAccessInvocationExpression->getArguments(),
            argumentTypeMismatch,
            typeCheckerResult
        );
    }
}