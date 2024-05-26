//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_PARAMETER_TYPE_CHECKER_POLICY_H
#define JETLANG_PARAMETER_TYPE_CHECKER_POLICY_H


#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"

namespace ParameterTypeCheckerPolicy {
    void apply(ASTFunctionParameterNode* functionParameter, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_PARAMETER_TYPE_CHECKER_POLICY_H
