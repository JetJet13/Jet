//
// Created by Johny Georges on 2024-05-28.
//

#ifndef JETLANG_ARRAY_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_ARRAY_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"

namespace ArrayExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTArrayExpressionNode> arrayExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_ARRAY_EXPRESSION_TYPE_CHECKER_POLICY_H
