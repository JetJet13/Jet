//
// Created by Johny Georges on 2024-04-02.
//

#ifndef JETLANG_CATCH_BLOCK_REDUCER_STRATEGY_H
#define JETLANG_CATCH_BLOCK_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class CatchBlockReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_CATCH_BLOCK_REDUCER_STRATEGY_H
