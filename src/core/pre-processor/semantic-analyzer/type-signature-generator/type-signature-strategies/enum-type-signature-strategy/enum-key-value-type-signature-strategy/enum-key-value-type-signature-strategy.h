//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_ENUM_KEY_VALUE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_ENUM_KEY_VALUE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-node.h"
#include "../../type-signature-strategy-provider.h"

class EnumKeyValueTypeSignatureStrategy {
public:
    LiteralTypeSignature* create(ASTEnumKeyValueNode* node, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_ENUM_KEY_VALUE_TYPE_SIGNATURE_STRATEGY_H
