//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_ELSE_BLOCK_REDUCER_STRATEGY_H
#define JETLANG_ELSE_BLOCK_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ElseBlockReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_ELSE_BLOCK_REDUCER_STRATEGY_H
