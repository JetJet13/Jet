//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../type-signature-strategy-provider.h"
#include "../../../../../../ast/ast-nodes/ast-statement-nodes/ast-class-property-ref-value-assignment-statement-node.h"

class ClassPropertyRefValueAssignmentStatementTypeSignatureStrategy {
public:
    void assign(ASTClassPropertyRefValueAssignmentStatementNode* classPropertyRefValueAssignmentStatementNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
