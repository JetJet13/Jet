//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_TRY_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_TRY_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-try-statement-node.h"

namespace TryStatementTypeCheckerPolicy {
    void apply(ASTTryStatementNode* tryStatementNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_TRY_STATEMENT_TYPE_CHECKER_POLICY_H
