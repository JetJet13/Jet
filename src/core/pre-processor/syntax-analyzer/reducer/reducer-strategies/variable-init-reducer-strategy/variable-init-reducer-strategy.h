//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_VARIABLE_INIT_REDUCER_STRATEGY_H
#define JETLANG_VARIABLE_INIT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class VariableInitReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_VARIABLE_INIT_REDUCER_STRATEGY_H
