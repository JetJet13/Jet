//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_IF_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_IF_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-if-statement-node.h"

namespace IfStatementTypeCheckerPolicy {
    void apply(ASTIfStatementNode* ifStatementNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_IF_STATEMENT_TYPE_CHECKER_POLICY_H
