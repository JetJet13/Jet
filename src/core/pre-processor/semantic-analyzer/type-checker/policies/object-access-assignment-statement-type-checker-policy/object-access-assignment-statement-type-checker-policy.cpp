//
// Created by Johny Georges on 2025-08-27.
//

#include "object-access-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"

namespace ObjectAccessAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTObjectAccessAssignmentStatementNode> objectAccessAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto objectAccessExpression = objectAccessAssignmentStatementNode->getObjectAccessAssignment()->getObjectAccess();
        auto sourceTypeSignature = objectAccessExpression->getSource()->getSource()->getTypeSignature();
        if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
            sourceTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature)->getUnderlyingType());
        }

        if (sourceTypeSignature->typeTargetIs(CLASS_INSTANCE_TYPE_SOURCE)) {
            auto classInstanceSource = std::dynamic_pointer_cast<ClassInstanceTypeSignature>(sourceTypeSignature);
            auto id = classInstanceSource->getClass()->addClassNameToKey(objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId());
            auto classProperty = classInstanceSource->getProperties()->find(id);
            if (classProperty && classProperty.value()->isConst()) {
                auto classPropertyAssignmentNotAllowedMessage = TypeCheckerErrorMessageTable::ClassPropertyAssignmentNotAllowed(objectAccessAssignmentStatementNode);
                typeCheckerResult->addError(classPropertyAssignmentNotAllowedMessage());
            }

            if (!fileScope->isClassScope() && classProperty && classProperty.value()->getAccessModifier()->isPrivate()) {
                auto classPropertyIsPrivateMessage = TypeCheckerErrorMessageTable::ClassPropertyIsPrivate(objectAccessAssignmentStatementNode);
                typeCheckerResult->addError(classPropertyIsPrivateMessage());
            }

        } else if (sourceTypeSignature->typeTargetIs(CLASS_TYPE_SOURCE)) {
            auto classSource = std::dynamic_pointer_cast<ClassTypeSignature>(sourceTypeSignature);
            auto id = classSource->addClassNameToKey(objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId());
            auto classStaticProperty = classSource->getStaticProperties()->find(id);
            if (classStaticProperty && classStaticProperty.value()->isConst()) {
                auto classPropertyAssignmentNotAllowedMessage = TypeCheckerErrorMessageTable::ClassPropertyAssignmentNotAllowed(objectAccessAssignmentStatementNode);
                typeCheckerResult->addError(classPropertyAssignmentNotAllowedMessage());
            }

            if (!fileScope->isClassScope() && classStaticProperty && classStaticProperty.value()->getAccessModifier()->isPrivate()) {
                auto classPropertyIsPrivateMessage = TypeCheckerErrorMessageTable::ClassPropertyIsPrivate(objectAccessAssignmentStatementNode);
                typeCheckerResult->addError(classPropertyIsPrivateMessage());
            }
        }

        auto statementUnknownMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeUnknown(objectAccessAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeInvalid(objectAccessAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeVoid(objectAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        objectAccessAssignmentStatementNode->getObjectAccessAssignment()->getTypeSignature(),
                        statementUnknownMessage,
                        statementInvalidMessage,
                        statementVoidMessage,
                        typeCheckerResult
                );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(objectAccessAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(objectAccessAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(objectAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            objectAccessAssignmentStatementNode->getExpression()->getTypeSignature(),
            expressionUnknownMessage,
            expressionInvalidMessage,
            expressionVoidMessage,
            typeCheckerResult
        );

        auto mismatchMessage = TypeCheckerErrorMessageTable::ObjectAccessAssignmentTypeMismatch(objectAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            objectAccessAssignmentStatementNode->getObjectAccessAssignment()->getTypeSignature(),
            objectAccessAssignmentStatementNode->getExpression()->getTypeSignature()->getTargetTypeSignature(),
            mismatchMessage,
            typeCheckerResult
        );

    }
}