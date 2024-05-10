//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_TYPE_SIGNATURE_STRATEGY_PROVIDER_H
#define JETLANG_TYPE_SIGNATURE_STRATEGY_PROVIDER_H

#include "type-signature-strategy-map.h"
#include "../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../../token/token-table.h"
#include "../../../../ast/ast-nodes/ast-node.h"


class TypeSignatureStrategyProvider {
private:
    TypeSignatureStrategyMap* _typeSignatureStrategyMap;
    TypeSignatureLookupTable* _typeSignatureLookupTable;
    TokenTable* _tokenTable;
public:
    explicit TypeSignatureStrategyProvider(TypeSignatureLookupTable* typeSignatureLookupTable, TokenTable* tokenTable);
    TypeSignature*  getTypeSignatureFor(ASTNode* node);
};

#endif //JETLANG_TYPE_SIGNATURE_STRATEGY_PROVIDER_H
