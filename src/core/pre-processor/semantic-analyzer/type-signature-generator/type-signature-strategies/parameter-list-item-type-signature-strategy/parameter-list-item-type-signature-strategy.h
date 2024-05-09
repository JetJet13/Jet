//
// Created by Johny Georges on 2024-05-04.
//

#ifndef JETLANG_PARAMETER_LIST_ITEM_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_PARAMETER_LIST_ITEM_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"


class ParameterListItemTypeSignatureStrategy {
public:
    TypeSignature* create(ASTFunctionParameterNode* node);
};

#endif //JETLANG_PARAMETER_LIST_ITEM_TYPE_SIGNATURE_STRATEGY_H
