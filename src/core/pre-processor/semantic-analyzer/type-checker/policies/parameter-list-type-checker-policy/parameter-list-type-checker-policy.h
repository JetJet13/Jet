//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_PARAMETER_LIST_TYPE_CHECKER_POLICY_H
#define JETLANG_PARAMETER_LIST_TYPE_CHECKER_POLICY_H

#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-node.h"
#include "../../types/type-checker-result/type-checker-result.h"

namespace ParameterListTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTFunctionParameterListNode> functionParameterList, TypeCheckerResult* typeCheckerResult);
};


#endif //JETLANG_PARAMETER_LIST_TYPE_CHECKER_POLICY_H
