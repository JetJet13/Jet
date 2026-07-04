//
// Created by Johny Georges on 2024-04-02.
//

#ifndef JETLANG_FINALLY_BLOCK_REDUCER_STRATEGY_H
#define JETLANG_FINALLY_BLOCK_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class FinallyBlockReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_FINALLY_BLOCK_REDUCER_STRATEGY_H
