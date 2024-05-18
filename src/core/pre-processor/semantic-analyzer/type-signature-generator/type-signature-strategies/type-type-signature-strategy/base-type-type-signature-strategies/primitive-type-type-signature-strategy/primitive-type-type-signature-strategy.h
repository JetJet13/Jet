//
// Created by Johny Georges on 2024-05-09.
//

#ifndef JETLANG_PRIMITIVE_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_PRIMITIVE_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-primitive-type-node.h"
#include "../../../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../../../type-signature-lookup-table/literal-type-signature-lookup-table/literal-type-signature-lookup-table.h"

class PrimitiveTypeTypeSignatureStrategy {
public:
    TypeSignature* create(ASTPrimitiveTypeNode* node, LiteralTypeSignatureLookupTable* literalTypeSignatureLookupTable);
};

#endif //JETLANG_PRIMITIVE_TYPE_TYPE_SIGNATURE_STRATEGY_H
