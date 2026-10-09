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

#include "object-access-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../../../type-signature/shared-type-signature/shared-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../../type-signature/invocable-type-signature/lambda-type-signature/lambda-type-signature.h"

void ObjectAccessInvocationExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> objectAccessInvocationExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getSource()->getSource(), context, scope);

    if (objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(SHARED_TYPE_SOURCE)) {
        auto sharedSource = std::dynamic_pointer_cast<SharedTypeSignature>(objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->getTargetTypeSignature());
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto sharedPrototypeTypeSignature = strategyMap->findSharedPtrPrototypeTypeSignature(id, sharedSource->getUnderlyingType());
        if (sharedPrototypeTypeSignature) {
            objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(sharedPrototypeTypeSignature.value());
            objectAccessInvocationExpression->setTypeSignature(sharedPrototypeTypeSignature.value()->getReturnType());
            strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getArguments(), std::make_shared<TypeSignatureContext>(objectAccessInvocationExpression->getInvocableTypeSignature()->getParameterTypes()), scope);
            return;
        }
    }

    auto sourceTypeSignature = objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->getTargetTypeSignature();
    if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
        sourceTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature)->getUnderlyingType());
    }

    if (sourceTypeSignature->typeSourceIs(STRUCT_TYPE_SOURCE)) {
        auto structSource = std::dynamic_pointer_cast<StructTypeSignature>(sourceTypeSignature->getTargetTypeSignature());
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto functionTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(structSource->getTypeSignatureForKey(id));
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(functionTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(functionTypeSignature->getReturnType());
        strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getArguments(), std::make_shared<TypeSignatureContext>(objectAccessInvocationExpression->getInvocableTypeSignature()->getParameterTypes()), scope);
        return;
    } else if (sourceTypeSignature->typeSourceIs(CLASS_INSTANCE_TYPE_SOURCE)) {
        auto classInstanceSource = std::dynamic_pointer_cast<ClassInstanceTypeSignature>(sourceTypeSignature);
        strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getArguments(), context, scope);
        auto id = FunctionIdGenerator::generateFor(objectAccessInvocationExpression->getName(), objectAccessInvocationExpression->getArguments()->getArgumentListTypeSignature()->toDetailString());
        auto classMethodTypeSignature = std::dynamic_pointer_cast<LambdaTypeSignature>(classInstanceSource->getKeyValuePairs()->find(id).value_or(std::make_shared<LambdaTypeSignature>()));
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(classMethodTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(classMethodTypeSignature->getReturnType());
        return;
    } else if (sourceTypeSignature->typeSourceIs(CLASS_TYPE_SOURCE)) {
        auto classSource = std::dynamic_pointer_cast<ClassTypeSignature>(sourceTypeSignature);
        strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getArguments(), context, scope);
        auto id = classSource->addClassNameToKey(FunctionIdGenerator::generateFor(objectAccessInvocationExpression->getName(), objectAccessInvocationExpression->getArguments()->getArgumentListTypeSignature()->toDetailString()));
        auto classStaticMethod = classSource->getStaticMethods()->find(id);
        if (classStaticMethod) {
            auto classStaticMethodTypeSignature = std::dynamic_pointer_cast<ClassMethodTypeSignature>(classStaticMethod.value());
            objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(classStaticMethodTypeSignature);
            objectAccessInvocationExpression->setTypeSignature(classStaticMethodTypeSignature->getReturnType());
            return;
        }
    } else if (sourceTypeSignature->typeSourceIs(ARRAY_TYPE_SOURCE)) {
        auto arraySource = std::dynamic_pointer_cast<ArrayTypeSignature>(sourceTypeSignature->getTargetTypeSignature());
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto arrayPrototypeTypeSignature = strategyMap->findArrayPrototypeTypeSignature(id, arraySource->getElementType()).value_or(std::make_shared<FunctionTypeSignature>());
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(arrayPrototypeTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(arrayPrototypeTypeSignature->getReturnType());
        strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getArguments(), std::make_shared<TypeSignatureContext>(objectAccessInvocationExpression->getInvocableTypeSignature()->getParameterTypes()), scope);
        return;
    } else if (sourceTypeSignature->typeSourceIs(STRING_LITERAL_TYPE_SOURCE)) {
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto arrayPrototypeTypeSignature = strategyMap->findStringPrototypeTypeSignature(id).value_or(std::make_shared<FunctionTypeSignature>());
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(arrayPrototypeTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(arrayPrototypeTypeSignature->getReturnType());
        strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getArguments(), std::make_shared<TypeSignatureContext>(objectAccessInvocationExpression->getInvocableTypeSignature()->getParameterTypes()), scope);
        return;
    }
    objectAccessInvocationExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
}
