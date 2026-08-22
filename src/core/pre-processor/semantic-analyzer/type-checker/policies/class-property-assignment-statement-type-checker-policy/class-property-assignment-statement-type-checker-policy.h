//
// Created by Johny Georges on 2024-05-28.
//

#ifndef JETLANG_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-class-property-assignment-statement-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ClassPropertyAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTClassPropertyAssignmentStatementNode> classPropertyAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
