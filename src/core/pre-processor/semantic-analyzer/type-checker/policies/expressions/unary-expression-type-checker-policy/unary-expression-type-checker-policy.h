//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_UNARY_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_UNARY_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"

namespace UnaryExpressionTypeCheckerPolicy {
    void apply(ASTUnaryExpressionNode* unaryExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_UNARY_EXPRESSION_TYPE_CHECKER_POLICY_H