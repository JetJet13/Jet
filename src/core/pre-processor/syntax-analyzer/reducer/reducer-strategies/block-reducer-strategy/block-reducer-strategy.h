//
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_BLOCK_REDUCER_STRATEGY_H
#define JETLANG_BLOCK_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class BlockReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_BLOCK_REDUCER_STRATEGY_H
