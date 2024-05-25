//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_PARAMETER_TYPE_CHECKER_POLICY_H
#define JETLANG_PARAMETER_TYPE_CHECKER_POLICY_H


#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"
#include "../../types/type-checker-rules/type-checker-rule-list.h"

namespace ParameterTypeCheckerPolicy {
    TypeCheckerResult apply(ASTFunctionParameterNode* functionParameter, TypeCheckerRuleList* rules);
};

#endif //JETLANG_PARAMETER_TYPE_CHECKER_POLICY_H
