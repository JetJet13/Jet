//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_PARAMETER_LIST_TYPE_CHECKER_POLICY_H
#define JETLANG_PARAMETER_LIST_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-node.h"

class ParameterListTypeCheckerPolicy {
public:
    TypeCheckerResult static verify(ASTFunctionParameterListNode* functionParameterList);
};


#endif //JETLANG_PARAMETER_LIST_TYPE_CHECKER_POLICY_H
