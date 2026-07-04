//
// Created by Johny Georges on 2025-02-17.
//

#ifndef JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-array-access-assignment-statement-node.h"

class ArrayAccessAssignmentStatementTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTArrayAccessAssignmentStatementNode> arrayAccessAssignmentStatement, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};


#endif //JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
