//
// Created by Johny Georges on 2025-10-16.
//

#ifndef JETLANG_TUPLE_ACCESS_ASSIGNMENT_REDUCER_STRATEGY_H
#define JETLANG_TUPLE_ACCESS_ASSIGNMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class TupleAccessAssignmentReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};


#endif //JETLANG_TUPLE_ACCESS_ASSIGNMENT_REDUCER_STRATEGY_H
