//
// Created by Johny Georges on 2024-05-11.
//

#include "new-class-instance-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void NewClassInstanceExpressionTypeSignatureStrategy::assign(ASTNewClassInstanceExpressionNode* newClassInstanceExpression, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignature = typeSignatureLookupTable->find(
            newClassInstanceExpression
            ->getClassName()
            ->getId()
    );
    strategyMap->assignTypeSignatureFor(newClassInstanceExpression->getArguments(), typeSignatureLookupTable);
    if (typeSignature->typeSourceIs(CLASS_TYPE_SOURCE)) {
        auto classTypeSignature = (ClassTypeSignature*)typeSignature;
        newClassInstanceExpression->setTypeSignature(
                new ClassInstanceTypeSignature(
                        classTypeSignature,
                        classTypeSignature->findConstructorForArguments(newClassInstanceExpression->getArguments()->getTypeSignature()->getArgumentTypes()))
                );
    } else {
        newClassInstanceExpression->setTypeSignature(new ClassInstanceTypeSignature());
    }


}