//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-module-access-ref-assignment-statement-node.h"

class ModuleAccessRefAssignmentStatementTypeSignatureStrategy {
public:
    void assign(ASTModuleAccessRefAssignmentStatementNode* moduleAccessRefAssignmentStatement, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};


#endif //JETLANG_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
