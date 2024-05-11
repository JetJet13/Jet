//
// Created by Johny Georges on 2024-05-09.
//

#ifndef JETLANG_LAMBDA_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_LAMBDA_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../type-signature/type-signature.h"
#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-lambda-type-node.h"
#include "../../../type-signature-strategy-provider.h"

class LambdaTypeTypeSignatureStrategy {
public:
    TypeSignature* create(ASTLambdaTypeNode* node, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_LAMBDA_TYPE_TYPE_SIGNATURE_STRATEGY_H
