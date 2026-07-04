//
// Created by Johny Georges on 2026-04-02.
//

#ifndef JETLANG_MODULE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_MODULE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-module-access-assignment-statement-node.h"

class ModuleAccessAssignmentStatementTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTModuleAccessAssignmentStatementNode> moduleAccessAssignmentStatement, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_MODULE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
