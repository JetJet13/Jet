//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_REF_VALUE_ASSIGNMENT_REDUCER_STRATEGY_H
#define JETLANG_REF_VALUE_ASSIGNMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class RefValueAssignmentReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_REF_VALUE_ASSIGNMENT_REDUCER_STRATEGY_H
