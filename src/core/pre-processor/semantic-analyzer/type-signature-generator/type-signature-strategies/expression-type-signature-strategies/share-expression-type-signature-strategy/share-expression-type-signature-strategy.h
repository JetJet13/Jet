//
// Created by Johny Georges on 2026-07-11.
//

#ifndef JETLANG_SHARE_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_SHARE_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../type-signature-strategy-provider.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-share-expression-node.h"

class ShareExpressionTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTShareExpressionNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_SHARE_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
