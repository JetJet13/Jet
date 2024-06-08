//
// Created by Johny Georges on 2024-06-08.
//

#ifndef JETLANG_PROCEDURE_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_PROCEDURE_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../type-signature/type-signature.h"
#include "../../../type-signature-strategy-provider.h"
#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-procedure-type-node.h"

class ProcedureTypeTypeSignatureStrategy {
public:
    void assign(ASTProcedureTypeNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_PROCEDURE_TYPE_TYPE_SIGNATURE_STRATEGY_H
