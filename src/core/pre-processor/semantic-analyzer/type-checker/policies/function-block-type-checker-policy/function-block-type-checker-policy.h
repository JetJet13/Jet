//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_FUNCTION_BLOCK_TYPE_CHECKER_POLICY_H
#define JETLANG_FUNCTION_BLOCK_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-block-node.h"
#include "../../types/type-checker-rules/type-checker-rule-list.h"

namespace FunctionBlockTypeCheckerPolicy {
    TypeCheckerResult apply(ASTFunctionBlockNode* functionBlock, TypeCheckerRuleList*);
};

#endif //JETLANG_FUNCTION_BLOCK_TYPE_CHECKER_POLICY_H
