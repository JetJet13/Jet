//
// Created by Johny Georges on 2024-05-09.
//

#include "this-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

TypeSignature* ThisTypeTypeSignatureStrategy::create(ASTThisTypeNode* node, TypeSignatureStrategyProvider* strategyMap) {

    return new InvalidTypeSignature();
}