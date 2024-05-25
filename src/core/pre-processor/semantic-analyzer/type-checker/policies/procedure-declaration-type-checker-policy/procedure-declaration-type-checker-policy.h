//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_PROCEDURE_DECLARATION_TYPE_CHECKER_POLICY_H
#define JETLANG_PROCEDURE_DECLARATION_TYPE_CHECKER_POLICY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../types/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"

class ProcedureDeclarationTypeCheckerPolicy {
public:
    TypeCheckerResult static verify(ASTProcedureDeclarationNode* procedureDeclarationNode);
};

#endif //JETLANG_PROCEDURE_DECLARATION_TYPE_CHECKER_POLICY_H
