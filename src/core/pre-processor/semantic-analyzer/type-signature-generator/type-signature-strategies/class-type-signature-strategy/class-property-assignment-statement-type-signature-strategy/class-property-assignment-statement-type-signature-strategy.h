//
// Created by Johny Georges on 2024-05-23.
//

#ifndef JETLANG_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../ast/ast-nodes/ast-statement-nodes/ast-class-property-assignment-statement-node.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../type-signature-strategy-provider.h"

class ClassPropertyAssignmentStatementTypeSignatureStrategy {
public:
    void assign(ASTClassPropertyAssignmentStatementNode* classPropertyAssignmentStatementNode, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
