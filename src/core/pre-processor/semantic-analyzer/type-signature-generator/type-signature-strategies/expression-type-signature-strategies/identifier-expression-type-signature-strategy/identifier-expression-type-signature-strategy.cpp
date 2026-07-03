//
// Created by Johny Georges on 2024-05-08.
//

#include "identifier-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void IdentifierExpressionTypeSignatureStrategy::assign(ASTIdentifierExpressionNode* identifierExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable) {
    auto id = identifierExpression->getId();
    auto typeSignature = typeSignatureLookupTable->find(id);
    if (typeSignature->isUnknown() && context->getTypeSignature() && context->getTypeSignature().value()->isInvocable()) {
        auto invocableTypeSignature = (InvocableTypeSignature*)context->getTypeSignature().value();
        auto functionTypeSignature = typeSignatureLookupTable->findGlobalFunction(id, FunctionIdGenerator::generateFor(invocableTypeSignature));
        if (functionTypeSignature) {
            identifierExpression->setTypeSignature(functionTypeSignature.value()->convertToVariableTypeSignature());
            return;
        }
    }
    identifierExpression->setTypeSignature(typeSignature);

}