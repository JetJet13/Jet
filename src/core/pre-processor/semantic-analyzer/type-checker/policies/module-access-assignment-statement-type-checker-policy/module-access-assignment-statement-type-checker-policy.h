//
// Created by Johny Georges on 2026-04-02.
//

#ifndef JETLANG_MODULE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_MODULE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-module-access-assignment-statement-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ModuleAccessAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTModuleAccessAssignmentStatementNode> moduleAccessAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_MODULE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
