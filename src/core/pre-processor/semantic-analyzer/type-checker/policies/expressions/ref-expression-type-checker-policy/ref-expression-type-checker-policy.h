//
// Created by Johny Georges on 2025-02-01.
//

#ifndef JETLANG_REF_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_REF_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-ref-expression-node.h"

namespace RefExpressionTypeCheckerPolicy {
    void apply(ASTRefExpressionNode* refExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_REF_EXPRESSION_TYPE_CHECKER_POLICY_H
