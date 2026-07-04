//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_IDENTIFIER_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_IDENTIFIER_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

namespace IdentifierExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTIdentifierExpressionNode> identifierExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_IDENTIFIER_EXPRESSION_TYPE_CHECKER_POLICY_H
