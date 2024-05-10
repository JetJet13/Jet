//
// Created by Johny Georges on 2024-05-04.
//

#include "parameter-list-type-singature-strategy.h"
#include "../../../../../type-signature/parameter-list-type-signature/parameter-list-type-signature.h"

TypeSignature* ParameterListTypeSignatureStrategy::create(ASTFunctionParameterListNode* node) {
    auto parameterListTypeSignature = new ParameterListTypeSignature({});
    return parameterListTypeSignature;
}