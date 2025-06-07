//
// Created by Johny Georges on 2025-06-07.
//

#ifndef JETLANG_CONCAT_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_CONCAT_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-concat-expression-node.h"

namespace ConcatExpressionTypeCheckerPolicy {
    void apply(ASTConcatExpressionNode* logicalExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_CONCAT_EXPRESSION_TYPE_CHECKER_POLICY_H
