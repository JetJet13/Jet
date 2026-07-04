//
// Created by Johny Georges on 2024-05-13.
//

#ifndef JETLANG_CLASS_PROPERTY_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-property-declaration-node.h"
#include "../../type-signature-strategy-provider.h"

class ClassPropertyTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTClassPropertyDeclarationNode> classPropertyDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_CLASS_PROPERTY_TYPE_SIGNATURE_STRATEGY_H
