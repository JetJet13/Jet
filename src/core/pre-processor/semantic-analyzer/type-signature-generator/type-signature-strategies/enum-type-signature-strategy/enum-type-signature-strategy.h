//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_ENUM_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_ENUM_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../../../../../token/token-table.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"
#include "../type-signature-strategy-provider.h"

class EnumTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTEnumDeclarationNode> enumDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_ENUM_TYPE_SIGNATURE_STRATEGY_H
