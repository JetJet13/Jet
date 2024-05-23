//
// Created by Johny Georges on 2024-05-22.
//

#ifndef JETLANG_IF_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_IF_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-if-statement-node.h"


class IfStatementTypeSignatureStrategy {
public:
    void assign(ASTIfStatementNode* ifStatementNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};


#endif //JETLANG_IF_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
