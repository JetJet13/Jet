//
// Created by Johny Georges on 2025-07-07.
//

#ifndef JETLANG_CUSTOM_TYPE_DECLARATION_ID_STRATEGY_H
#define JETLANG_CUSTOM_TYPE_DECLARATION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ast-node-id-strategy.h"

class CustomTypeDeclarationIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
public:
    void assign(ASTNode* node) override;
};

#endif //JETLANG_CUSTOM_TYPE_DECLARATION_ID_STRATEGY_H
