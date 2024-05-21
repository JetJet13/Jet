//
// Created by Johny Georges on 2024-05-20.
//

#ifndef JETLANG_IDENTIFIER_EXPRESSION_ID_STRATEGY_H
#define JETLANG_IDENTIFIER_EXPRESSION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ast-node-id-strategy.h"

class IdentifierExpressionIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
public:
    void assign(ASTNode* node) override;
};

#endif //JETLANG_IDENTIFIER_EXPRESSION_ID_STRATEGY_H
