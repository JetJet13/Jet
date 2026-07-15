//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../type-signature-strategy-provider.h"
#include "../../../../../../ast/ast-nodes/ast-statement-nodes/ast-class-property-shared-value-assignment-statement-node.h"

class ClassPropertySharedValueAssignmentStatementTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTClassPropertySharedValueAssignmentStatementNode> classPropertySharedValueAssignmentStatementNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
