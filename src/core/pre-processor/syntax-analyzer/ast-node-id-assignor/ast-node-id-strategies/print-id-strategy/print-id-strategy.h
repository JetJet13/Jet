//
// Created by Johny Georges on 2025-07-21.
//

#ifndef JETLANG_PRINT_ID_STRATEGY_H
#define JETLANG_PRINT_ID_STRATEGY_H

#include "../ast-node-id-strategy.h"

class PrintIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
public:
    void assign(ASTNode* node) override;
};

#endif //JETLANG_PRINT_ID_STRATEGY_H
