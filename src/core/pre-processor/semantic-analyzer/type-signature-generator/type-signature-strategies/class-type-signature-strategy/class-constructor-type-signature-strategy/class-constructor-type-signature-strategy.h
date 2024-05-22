//
// Created by Johny Georges on 2024-05-13.
//

#ifndef JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_STRATEGY_H

#include "../../type-signature-strategy-provider.h"
#include "../../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-constructor-declaration-node.h"

class ClassConstructorTypeSignatureStrategy {
public:
    void assign(ASTClassConstructorDeclarationNode* classConstructorDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_STRATEGY_H
