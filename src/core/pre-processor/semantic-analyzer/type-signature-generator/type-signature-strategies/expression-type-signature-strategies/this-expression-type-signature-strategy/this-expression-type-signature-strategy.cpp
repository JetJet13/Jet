//
// Created by Johny Georges on 2024-05-11.
//

#include "this-expression-type-signature-strategy.h"

void ThisExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTThisExpressionNode> thisExpression, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable) {
    thisExpression->setTypeSignature(typeSignatureLookupTable->find(thisExpression->getId())->convertToVariableTypeSignature());
}