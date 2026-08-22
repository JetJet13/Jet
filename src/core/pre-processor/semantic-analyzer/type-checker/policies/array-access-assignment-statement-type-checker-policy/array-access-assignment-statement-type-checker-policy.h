//
// Created by Johny Georges on 2025-02-17.
//

#ifndef JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-array-access-assignment-statement-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ArrayAccessAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTArrayAccessAssignmentStatementNode> arrayAccessAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};


#endif //JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
