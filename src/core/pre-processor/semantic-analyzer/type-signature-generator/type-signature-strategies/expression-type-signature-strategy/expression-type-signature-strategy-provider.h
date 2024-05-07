//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_EXPRESSION_TYPE_SIGNATURE_STRATEGY_PROVIDER_H
#define JETLANG_EXPRESSION_TYPE_SIGNATURE_STRATEGY_PROVIDER_H

#include "expression-type-signature-strategy-map.h"
#include "../../../../../ast/types/ast-node-type.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"


class ExpressionTypeSignatureStrategyProvider {
private:
    ExpressionTypeSignatureStrategyMap* _expressionTypeSignatureStrategyMap;
    TypeSignatureLookupTable* _typeSignatureLookupTable;
public:
    ExpressionTypeSignatureStrategyProvider(TypeSignatureLookupTable* typeSignatureLookupTable);
    TypeSignature*  getTypeSignatureForExpression(ASTNode* node);

};

#endif //JETLANG_EXPRESSION_TYPE_SIGNATURE_STRATEGY_PROVIDER_H
