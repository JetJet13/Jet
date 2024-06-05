//
// Created by Johny Georges on 2024-06-05.
//

#ifndef JETLANG_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_ID_STRATEGY_H
#define JETLANG_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ast-node-id-strategy.h"

class UseManyByWildcardModuleDeclarationIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
public:
    void assign(ASTNode* node) override;
};

#endif //JETLANG_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_ID_STRATEGY_H
