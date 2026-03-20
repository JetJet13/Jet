//
// Created by Johny Georges on 2024-05-09.
//

#ifndef JETLANG_TUPLE_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_TUPLE_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../type-signature/type-signature.h"
#include "../../../type-signature-strategy-provider.h"
#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-tuple-type-nodes/ast-tuple-type-node.h"

class TupleTypeTypeSignatureStrategy {
public:
    void assign(ASTTupleTypeNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_TUPLE_TYPE_TYPE_SIGNATURE_STRATEGY_H
