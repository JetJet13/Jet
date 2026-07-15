//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-tuple-access-shared-value-assignment-statement-node.h"

class TupleAccessSharedValueAssignmentStatementTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTTupleAccessSharedValueAssignmentStatementNode> tupleAccessSharedValueAssignmentStatement, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
