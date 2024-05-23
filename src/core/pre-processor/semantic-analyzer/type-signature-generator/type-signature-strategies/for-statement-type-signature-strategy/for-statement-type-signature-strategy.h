//
// Created by Johny Georges on 2024-05-23.
//

#ifndef JETLANG_FOR_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_FOR_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-for-statement-node.h"

class ForStatementTypeSignatureStrategy {
public:
    void assign(ASTForStatementNode* forStatementNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_FOR_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
