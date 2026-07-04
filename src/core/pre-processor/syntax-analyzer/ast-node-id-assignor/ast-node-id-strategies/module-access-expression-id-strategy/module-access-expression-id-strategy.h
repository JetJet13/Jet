//
// Created by Johny Georges on 2024-11-06.
//

#ifndef JETLANG_MODULE_ACCESS_EXPRESSION_ID_STRATEGY_H
#define JETLANG_MODULE_ACCESS_EXPRESSION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ast-node-id-strategy.h"

class ModuleAccessExpressionIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
public:
    void assign(std::shared_ptr<ASTNode> node) override;
};

#endif //JETLANG_MODULE_ACCESS_EXPRESSION_ID_STRATEGY_H
