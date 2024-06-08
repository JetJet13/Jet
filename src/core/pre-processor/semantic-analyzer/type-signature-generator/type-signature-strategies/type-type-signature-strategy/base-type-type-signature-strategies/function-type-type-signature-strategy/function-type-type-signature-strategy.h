//
// Created by Johny Georges on 2024-06-08.
//

#ifndef JETLANG_FUNCTION_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_FUNCTION_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../type-signature/type-signature.h"
#include "../../../type-signature-strategy-provider.h"
#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-function-type-node.h"

class FunctionTypeTypeSignatureStrategy {
public:
    void assign(ASTFunctionTypeNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_FUNCTION_TYPE_TYPE_SIGNATURE_STRATEGY_H
