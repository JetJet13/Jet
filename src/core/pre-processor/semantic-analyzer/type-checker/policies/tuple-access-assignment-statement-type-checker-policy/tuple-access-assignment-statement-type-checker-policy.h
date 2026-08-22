//
// Created by Johny Georges on 2025-10-16.
//

#ifndef JETLANG_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-tuple-access-assignment-statement-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace TupleAccessAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTTupleAccessAssignmentStatementNode> tupleAccessAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
}


#endif //JETLANG_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
