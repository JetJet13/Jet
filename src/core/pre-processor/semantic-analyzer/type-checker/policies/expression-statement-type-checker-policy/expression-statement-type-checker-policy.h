//
// Created by Johny Georges on 2024-05-28.
//

#ifndef JETLANG_EXPRESSION_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_EXPRESSION_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-expression-statement-node.h"

namespace ExpressionStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTExpressionStatementNode> expressionStatementNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_EXPRESSION_STATEMENT_TYPE_CHECKER_POLICY_H
