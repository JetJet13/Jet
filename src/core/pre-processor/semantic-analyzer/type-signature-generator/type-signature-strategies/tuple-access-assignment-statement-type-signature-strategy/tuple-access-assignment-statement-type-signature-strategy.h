//
// Created by Johny Georges on 2025-10-16.
//

#ifndef JETLANG_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-tuple-access-assignment-statement-node.h"

class TupleAccessAssignmentStatementTypeSignatureStrategy {
public:
    void assign(ASTTupleAccessAssignmentStatementNode* tupleAccessAssignmentStatement, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
