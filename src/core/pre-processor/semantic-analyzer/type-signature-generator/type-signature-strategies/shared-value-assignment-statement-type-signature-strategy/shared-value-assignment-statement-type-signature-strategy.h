//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-shared-value-assignment-statement-node.h"

class SharedValueAssignmentStatementTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTSharedValueAssignmentStatementNode> sharedValueAssignmentStatement, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
