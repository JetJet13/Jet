//
// Created by Johny Georges on 2024-05-07.
//

#include "class-property-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-property-type-signature/class-property-type-signature.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../../../../type-signature/class-type-signature/class-type-signature.h"

void ClassPropertyAccessExpressionTypeSignatureStrategy::assign(ASTClassPropertyAccessExpressionNode* classPropertyAccessExpression, TypeSignatureLookupTable* scope) {
    auto classTypeSignature = (ClassTypeSignature*)scope->find(classPropertyAccessExpression->getPropertyAccess()->getClassAccess()->getThis()->getId());
//    Logger::log("class type id", classPropertyAccessExpression->getPropertyAccess()->getClassAccess()->getThis()->getId());
//    Logger::log("ClassPropertyAccessExpressionTypeSignatureStrategy", "id", classPropertyAccessExpression->getPropertyAccess()->getPropertyName()->getId());
//    classTypeSignature->print();
//    classTypeSignature->getProperties()->print();
//    classTypeSignature->getMethods()->print();
//    classTypeSignature->getConstructors()->print();
//    Logger::log("!!!----");
    auto classPropertyTypeSignature = classTypeSignature->getProperties()->find(classPropertyAccessExpression->getPropertyAccess()->getPropertyName()->getId());
    if (!classPropertyTypeSignature) {
        auto classMethodTypeSignature = classTypeSignature->getMethods()->find(classPropertyAccessExpression->getPropertyAccess()->getPropertyName()->getId());
        if (!classMethodTypeSignature) {
            Logger::log("!classMethodTypeSignature and !classPropertyTypeSignature", classPropertyAccessExpression->getPropertyAccess()->getPropertyName()->getId());
            classPropertyAccessExpression->setTypeSignature(new InvalidTypeSignature());
            return;
        }
        Logger::log("classMethodTypeSignature.value()", classMethodTypeSignature.value()->toString());
        classPropertyAccessExpression->setTypeSignature(classMethodTypeSignature.value());
        classPropertyAccessExpression->getTypeSignature()->print();
        return;
    }
    classPropertyTypeSignature.value()->print();
    classPropertyAccessExpression->setTypeSignature(classPropertyTypeSignature.value()->getType());
}