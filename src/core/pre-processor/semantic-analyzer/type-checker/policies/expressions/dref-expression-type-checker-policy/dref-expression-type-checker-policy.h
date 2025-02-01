//
// Created by Johny Georges on 2025-02-01.
//

#ifndef JETLANG_DREF_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_DREF_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-dref-expression-node.h"

namespace DrefExpressionTypeCheckerPolicy {
    void apply(ASTDrefExpressionNode* drefExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_DREF_EXPRESSION_TYPE_CHECKER_POLICY_H
