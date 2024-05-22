//
// Created by Johny Georges on 2024-05-13.
//

#ifndef JETLANG_PROCEDURE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_PROCEDURE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"

class ProcedureTypeSignatureStrategy {
public:
    void assign(ASTProcedureDeclarationNode* procedureDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_PROCEDURE_TYPE_SIGNATURE_STRATEGY_H
