//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_USE_MANY_MODULE_DECLARATION_ID_STRATEGY_H
#define JETLANG_USE_MANY_MODULE_DECLARATION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ast-node-id-strategy.h"

class UseManyModuleDeclarationIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
public:
    void assign(std::shared_ptr<ASTNode> node) override;
};

#endif //JETLANG_USE_MANY_MODULE_DECLARATION_ID_STRATEGY_H
