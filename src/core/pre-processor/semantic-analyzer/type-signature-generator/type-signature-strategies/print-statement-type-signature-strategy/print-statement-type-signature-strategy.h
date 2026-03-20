//
// Created by Johny Georges on 2025-07-21.
//

#ifndef JETLANG_PRINT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_PRINT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-print-statement-node.h"

class PrintStatementTypeSignatureStrategy {
public:
    void assign(ASTPrintStatementNode* printStatementNode, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_PRINT_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
