//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ArrayAccessSharedValueAssignmentStatementReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
