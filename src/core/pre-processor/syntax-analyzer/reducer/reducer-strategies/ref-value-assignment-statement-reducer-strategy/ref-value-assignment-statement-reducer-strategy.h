//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_REF_VALUE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
#define JETLANG_REF_VALUE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class RefValueAssignmentStatementReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_REF_VALUE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
