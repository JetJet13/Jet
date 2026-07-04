//
// Created by Johny Georges on 2025-08-27.
//

#ifndef JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-object-access-assignment-statement-node.h"

class ObjectAccessAssignmentStatementTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTObjectAccessAssignmentStatementNode> objectAccessAssignmentStatement, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
