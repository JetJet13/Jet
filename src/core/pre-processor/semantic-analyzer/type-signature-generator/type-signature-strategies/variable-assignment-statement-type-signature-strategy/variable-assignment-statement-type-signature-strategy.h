//
// Created by Johny Georges on 2024-05-22.
//

#ifndef JETLANG_VARIABLE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_VARIABLE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-variable-assignment-statement-node.h"

class VariableAssignmentStatementTypeSignatureStrategy {
public:
    void assign(ASTVariableAssignmentStatementNode* variableAssignmentStatement, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_VARIABLE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
