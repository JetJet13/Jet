//
// Created by Johny Georges on 2024-05-09.
//

#ifndef JETLANG_INT_LITERAL_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_INT_LITERAL_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-int-literal-type-node.h"

class IntLiteralTypeTypeSignatureStrategy {
public:
    TypeSignature* create(ASTIntLiteralTypeNode* node, TokenTable* tokenTable);
};

#endif //JETLANG_INT_LITERAL_TYPE_TYPE_SIGNATURE_STRATEGY_H
