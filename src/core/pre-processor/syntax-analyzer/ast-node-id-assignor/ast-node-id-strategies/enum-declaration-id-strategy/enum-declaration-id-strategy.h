//
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_ENUM_DECLARATION_ID_STRATEGY_H
#define JETLANG_ENUM_DECLARATION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ast-node-id-strategy.h"

class EnumDeclarationIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
public:
    void assign(std::shared_ptr<ASTNode> node) override;
};

#endif //JETLANG_ENUM_DECLARATION_ID_STRATEGY_H
