//
// Created by Johny Georges on 2024-05-29.
//

#include "object-access-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"

namespace ObjectAccessExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTObjectAccessExpressionNode> objectAccessExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto sourceTypeSignature = objectAccessExpression->getSource()->getSource()->getTypeSignature();
        if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
            sourceTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature)->getUnderlyingType());
        }

        if (sourceTypeSignature->typeTargetIs(CLASS_INSTANCE_TYPE_SOURCE)) {
            auto classInstanceSource = std::dynamic_pointer_cast<ClassInstanceTypeSignature>(sourceTypeSignature);
            auto id = classInstanceSource->getClass()->addClassNameToKey(objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId());
            auto classProperty = classInstanceSource->getProperties()->find(id);

            if (!fileScope->isClassScope() && classProperty && classProperty.value()->getAccessModifier()->isPrivate()) {
                auto classPropertyIsPrivateMessage = TypeCheckerErrorMessageTable::ClassPropertyIsPrivate(objectAccessExpression);
                typeCheckerResult->addError(classPropertyIsPrivateMessage());
            }

        } else if (sourceTypeSignature->typeTargetIs(CLASS_TYPE_SOURCE)) {
            auto classSource = std::dynamic_pointer_cast<ClassTypeSignature>(sourceTypeSignature);
            auto id = classSource->addClassNameToKey(objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId());
            auto classStaticProperty = classSource->getStaticProperties()->find(id);

            if (!fileScope->isClassScope() && classStaticProperty && classStaticProperty.value()->getAccessModifier()->isPrivate()) {
                auto classPropertyIsPrivateMessage = TypeCheckerErrorMessageTable::ClassPropertyIsPrivate(objectAccessExpression);
                typeCheckerResult->addError(classPropertyIsPrivateMessage());
            }
        }

        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(objectAccessExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(objectAccessExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(objectAccessExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            objectAccessExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
    }
}