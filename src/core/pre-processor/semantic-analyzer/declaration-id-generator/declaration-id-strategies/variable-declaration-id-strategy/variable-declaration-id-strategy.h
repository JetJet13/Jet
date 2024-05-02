//
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_VARIABLE_DECLARATION_ID_STRATEGY_H
#define JETLANG_VARIABLE_DECLARATION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../declaration-id-strategy.h"

class VariableDeclarationIdStrategy : public DeclarationIdStrategy {
    using DeclarationIdStrategy::DeclarationIdStrategy;
public:
    DeclarationId* generate(ASTNode* node) override;
};

#endif //JETLANG_VARIABLE_DECLARATION_ID_STRATEGY_H
