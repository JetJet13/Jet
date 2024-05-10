//
// Created by Johny Georges on 2024-05-04.
//

#include "parameter-list-item-type-signature-strategy.h"
#include "../../../../../type-signature/parameter-list-type-signature/parameter-list-item-type-signature/parameter-list-item-type-signature.h"
#include "../../../../../type-signature/literal-type-signature/int-literal-type-signature.h"

TypeSignature* ParameterListItemTypeSignatureStrategy::create(ASTFunctionParameterNode* node) {
    // todo: parameter list item type signature strategy
    //  needs to generate a type-signature from an ASTTypeNode.
    auto parameterListTypeItemSignature = new ParameterListItemTypeSignature(node->getId(), new IntLiteralTypeSignature());
    return parameterListTypeItemSignature;
}