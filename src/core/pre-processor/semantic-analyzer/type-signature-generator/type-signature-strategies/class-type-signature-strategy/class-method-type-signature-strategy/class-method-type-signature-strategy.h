//
// Created by Johny Georges on 2024-05-13.
//

#ifndef JETLANG_CLASS_METHOD_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CLASS_METHOD_TYPE_SIGNATURE_STRATEGY_H

#include "../../type-signature-strategy-provider.h"
#include "../../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-method-declaration-node.h"

class ClassMethodTypeSignatureStrategy {
public:
    ClassMethodTypeSignature* create(ASTClassMethodDeclarationNode* classMethodDeclaration, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_CLASS_METHOD_TYPE_SIGNATURE_STRATEGY_H
