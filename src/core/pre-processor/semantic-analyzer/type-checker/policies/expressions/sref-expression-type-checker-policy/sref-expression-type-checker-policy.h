//
// Created by Johny Georges on 2025-03-29.
//

#ifndef JETLANG_SREF_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_SREF_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-sref-expression-node.h"

namespace SrefExpressionTypeCheckerPolicy {
    void apply(ASTSrefExpressionNode* srefExpression, TypeCheckerResult* typeCheckerResult);
}


#endif //JETLANG_SREF_EXPRESSION_TYPE_CHECKER_POLICY_H
