//
// Created by Johny Georges on 2026-07-11.
//

#ifndef JETLANG_SHARE_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_SHARE_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-share-expression-node.h"

namespace ShareExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTShareExpressionNode> shareExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_SHARE_EXPRESSION_TYPE_CHECKER_POLICY_H
