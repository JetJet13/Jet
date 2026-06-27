//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ArrayAccessRefAssignmentStatementReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
