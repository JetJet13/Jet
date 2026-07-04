//
// Created by Johny Georges on 2024-05-23.
//

#ifndef JETLANG_FOR_IN_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_FOR_IN_STATEMENT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-for-in-statement-node.h"

class ForInStatementTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTForInStatementNode> forStatementNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_FOR_IN_STATEMENT_TYPE_SIGNATURE_STRATEGY_H
