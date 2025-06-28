//
// Created by Johny Georges on 2025-06-28.
//

#ifndef JETLANG_STRUCT_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_STRUCT_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../type-signature-strategy-provider.h"
#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-struct-type-nodes/ast-struct-type-node.h"

class StructTypeTypeSignatureStrategy {
public:
    void assign(ASTStructTypeNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_STRUCT_TYPE_TYPE_SIGNATURE_STRATEGY_H
