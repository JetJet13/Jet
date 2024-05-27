//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_FOR_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_FOR_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-for-statement-node.h"

namespace ForStatementTypeCheckerPolicy {
    void apply(ASTForStatementNode* forStatementNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_FOR_STATEMENT_TYPE_CHECKER_POLICY_H
