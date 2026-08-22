//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_PROCEDURE_DECLARATION_TYPE_CHECKER_POLICY_H
#define JETLANG_PROCEDURE_DECLARATION_TYPE_CHECKER_POLICY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"
#include "../../types/type-checker-result/type-checker-result.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ProcedureDeclarationTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTProcedureDeclarationNode> procedureDeclarationNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_PROCEDURE_DECLARATION_TYPE_CHECKER_POLICY_H
