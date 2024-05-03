//
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_ENUM_DECLARATION_ID_STRATEGY_H
#define JETLANG_ENUM_DECLARATION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../declaration-id-strategy.h"

class EnumDeclarationIdStrategy : public DeclarationIdStrategy {
    using DeclarationIdStrategy::DeclarationIdStrategy;
public:
    void assign(ASTNode* node) override;
};

#endif //JETLANG_ENUM_DECLARATION_ID_STRATEGY_H
