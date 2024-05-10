//
// Created by Johny Georges on 2024-05-04.
//

#ifndef JETLANG_PARAMETER_LIST_TYPE_SINGATURE_STRATEGY_H
#define JETLANG_PARAMETER_LIST_TYPE_SINGATURE_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-node.h"
#include "../../../../../type-signature/type-signature.h"

class ParameterListTypeSignatureStrategy {
public:
    TypeSignature* create(ASTFunctionParameterListNode* node);
};

#endif //JETLANG_PARAMETER_LIST_TYPE_SINGATURE_STRATEGY_H
