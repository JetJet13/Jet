//
// Created by Johny Georges on 2025-07-12.
//

#ifndef JETLANG_LAMBDA_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_LAMBDA_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../type-signature/type-signature.h"
#include "../../../type-signature-strategy-provider.h"
#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-lambda-type-nodes/ast-lambda-type-node.h"

class LambdaTypeTypeSignatureStrategy {
public:
    void assign(ASTLambdaTypeNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_LAMBDA_TYPE_TYPE_SIGNATURE_STRATEGY_H
