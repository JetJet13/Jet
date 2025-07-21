//
// Created by Johny Georges on 2025-07-21.
//

#ifndef JETLANG_PRINT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_PRINT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-print-statement-node.h"

namespace PrintStatementTypeCheckerPolicy {
    void apply(ASTPrintStatementNode* printStatementNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_PRINT_STATEMENT_TYPE_CHECKER_POLICY_H
