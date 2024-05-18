//
// Created by Johny Georges on 2024-05-13.
//

#ifndef JETLANG_LITERAL_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_LITERAL_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../../../../../ast/ast-nodes/ast-literal-nodes/ast-literal-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../type-signature-lookup-table/literal-type-signature-lookup-table/literal-type-signature-lookup-table.h"

class LiteralTypeSignatureStrategy {
public:
    LiteralTypeSignature* create(ASTLiteralNode* literalNode, LiteralTypeSignatureLookupTable* literalTypeSignatureLookupTable);
};

#endif //JETLANG_LITERAL_TYPE_SIGNATURE_STRATEGY_H
