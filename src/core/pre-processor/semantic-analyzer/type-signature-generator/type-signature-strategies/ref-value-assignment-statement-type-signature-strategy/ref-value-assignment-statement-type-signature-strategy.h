//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_REF_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_REF_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-ref-value-assignment-statement-node.h"

class RefValueAssignmentStatementTypeSignatureStrategy {
public:
    void assign(ASTRefValueAssignmentStatementNode* refValueAssignmentStatement, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_REF_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
