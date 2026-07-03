//
// Created by Johny Georges on 2025-07-07.
//

#ifndef JETLANG_CUSTOM_TYPE_DECLARATION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CUSTOM_TYPE_DECLARATION_TYPE_SIGNATURE_STRATEGY_H

#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-custom-type-declaration-node.h"

class CustomTypeDeclarationTypeSignatureStrategy {
public:
    void assignAndAddToScope(ASTCustomTypeDeclarationNode* customTypeDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};


#endif //JETLANG_CUSTOM_TYPE_DECLARATION_TYPE_SIGNATURE_STRATEGY_H
