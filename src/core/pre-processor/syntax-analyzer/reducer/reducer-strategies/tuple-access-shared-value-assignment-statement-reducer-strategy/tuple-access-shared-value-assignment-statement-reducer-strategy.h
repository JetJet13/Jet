//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
#define JETLANG_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class TupleAccessSharedValueAssignmentStatementReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
