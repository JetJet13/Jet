//
// Created by Johny Georges on 2024-03-12.
//

#ifndef JETLANG_ARRAY_ACCESS_REDUCER_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_REDUCER_STRATEGY_H

#include "../reducer-strategy.h"

class ArrayAccessReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_ARRAY_ACCESS_REDUCER_STRATEGY_H
