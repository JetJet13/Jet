//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_VARIABLE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
#define JETLANG_VARIABLE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class VariableAssignmentStatementReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};


#endif //JETLANG_VARIABLE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
