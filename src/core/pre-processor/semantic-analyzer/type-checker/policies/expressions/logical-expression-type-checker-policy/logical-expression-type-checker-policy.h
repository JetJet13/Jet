//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_LOGICAL_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_LOGICAL_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"

namespace LogicalExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTLogicalExpressionNode> logicalExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_LOGICAL_EXPRESSION_TYPE_CHECKER_POLICY_H
