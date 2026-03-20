//
// Created by Johny Georges on 2024-05-23.
//

#ifndef JETLANG_WHILE_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_WHILE_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-while-statement-node.h"


class WhileStatementTypeSignatureStrategy {
public:
    void assign(ASTWhileStatementNode* whileStatementNode, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};


#endif //JETLANG_WHILE_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
