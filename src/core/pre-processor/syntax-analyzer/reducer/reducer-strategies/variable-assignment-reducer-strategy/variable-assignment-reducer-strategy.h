//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_VARIABLE_ASSIGNMENT_REDUCER_STRATEGY_H
#define JETLANG_VARIABLE_ASSIGNMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class VariableAssignmentReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_VARIABLE_ASSIGNMENT_REDUCER_STRATEGY_H
