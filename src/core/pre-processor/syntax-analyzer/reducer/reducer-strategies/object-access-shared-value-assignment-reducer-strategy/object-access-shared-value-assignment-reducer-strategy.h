//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_REDUCER_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ObjectAccessSharedValueAssignmentReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_REDUCER_STRATEGY_H
