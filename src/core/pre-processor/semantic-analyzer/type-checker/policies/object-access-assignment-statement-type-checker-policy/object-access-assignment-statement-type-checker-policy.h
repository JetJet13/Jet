//
// Created by Johny Georges on 2025-08-27.
//

#ifndef JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-object-access-assignment-statement-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ObjectAccessAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTObjectAccessAssignmentStatementNode> objectAccessAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
}

#endif //JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
