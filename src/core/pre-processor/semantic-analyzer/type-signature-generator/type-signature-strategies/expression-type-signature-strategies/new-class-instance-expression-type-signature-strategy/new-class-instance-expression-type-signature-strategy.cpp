//
// Created by Johny Georges on 2024-05-11.
//

#include "new-class-instance-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void NewClassInstanceExpressionTypeSignatureStrategy::assign(ASTNewClassInstanceExpressionNode* newClassInstanceExpression, TypeSignatureContext* context, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto moduleName = newClassInstanceExpression->getModuleName();
    auto typeSignature = moduleName
            ? typeSignatureLookupTable->find(moduleName.value(), newClassInstanceExpression->getClassName())
            : typeSignatureLookupTable->find(newClassInstanceExpression->getClassName());
    strategyMap->assignTypeSignatureFor(newClassInstanceExpression->getArguments(), context, typeSignatureLookupTable);
    if (typeSignature->typeSourceIs(CLASS_TYPE_SOURCE)) {
        auto classTypeSignature = (ClassTypeSignature*)typeSignature;
        newClassInstanceExpression->setTypeSignature(
                new NewClassInstanceTypeSignature(
                        classTypeSignature,
                        classTypeSignature->findConstructorForArguments(newClassInstanceExpression->getArguments()->getTypeSignature()->getArgumentTypes()))
                );
        newClassInstanceExpression->getTypeSignature()->setModuleId(classTypeSignature->getModuleId());
        newClassInstanceExpression->getTypeSignature()->setId(newClassInstanceExpression->getClassName());
    } else {
        newClassInstanceExpression->setTypeSignature(new NewClassInstanceTypeSignature());
    }
}