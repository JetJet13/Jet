//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_FOR_IN_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_FOR_IN_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-for-in-statement-node.h"

namespace ForInStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTForInStatementNode> forStatementNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_FOR_IN_STATEMENT_TYPE_CHECKER_POLICY_H
