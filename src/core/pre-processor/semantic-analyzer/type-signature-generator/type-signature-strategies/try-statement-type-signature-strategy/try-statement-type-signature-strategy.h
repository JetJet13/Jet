//
// Created by Johny Georges on 2024-05-23.
//

#ifndef JETLANG_TRY_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_TRY_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-try-statement-node.h"

class TryStatementTypeSignatureStrategy {
public:
    void assign(ASTTryStatementNode* tryStatementNode, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_TRY_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
