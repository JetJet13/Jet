//
// Created by Johny Georges on 2025-02-17.
//

#ifndef JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ArrayAccessAssignmentStatementReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
