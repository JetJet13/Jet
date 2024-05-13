//
// Created by Johny Georges on 2024-05-13.
//

#ifndef JETLANG_FUNCTION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_FUNCTION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"

class FunctionTypeSignatureStrategy {
public:
    TypeSignature* create(ASTFunctionDeclarationNode* functionDeclaration, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_FUNCTION_TYPE_SIGNATURE_STRATEGY_H
