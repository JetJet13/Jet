//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_SHARED_VALUE_ASSIGNMENT_REDUCER_STRATEGY_H
#define JETLANG_SHARED_VALUE_ASSIGNMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class SharedValueAssignmentReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_SHARED_VALUE_ASSIGNMENT_REDUCER_STRATEGY_H
