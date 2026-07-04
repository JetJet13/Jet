//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_CURRY_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_CURRY_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-curry-expression-node.h"

namespace CurryExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTCurryExpressionNode> curryExpression, TypeCheckerResult* typeCheckerResult);
};


#endif //JETLANG_CURRY_EXPRESSION_TYPE_CHECKER_POLICY_H
