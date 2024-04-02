//
// Created by Johny Georges on 2024-04-02.
//

#ifndef JETLANG_CATCH_BLOCK_REDUCER_STRATEGY_H
#define JETLANG_CATCH_BLOCK_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class CatchBlockReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_CATCH_BLOCK_REDUCER_STRATEGY_H
