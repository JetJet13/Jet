//
// Created by Johny Georges on 2024-05-13.
//

#ifndef JETLANG_VARIABLE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_VARIABLE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"

class VariableTypeSignatureStrategy {
public:
    TypeSignature* create(ASTVariableDeclarationNode* variableDeclaration, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_VARIABLE_TYPE_SIGNATURE_STRATEGY_H
