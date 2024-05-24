//
// Created by Johny Georges on 2024-05-21.
//

#ifndef JETLANG_VARIABLE_DECLARATION_TYPE_CHECKER_POLICY_H
#define JETLANG_VARIABLE_DECLARATION_TYPE_CHECKER_POLICY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../types/type-checker-result.h"

class VariableDeclarationTypeCheckerPolicy {
public:
    TypeCheckerResult static verify(ASTVariableDeclarationNode* variableDeclarationNode);
};

#endif //JETLANG_VARIABLE_DECLARATION_TYPE_CHECKER_POLICY_H
