//
// Created by Johny Georges on 2025-08-27.
//

#ifndef JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ObjectAccessAssignmentStatementReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
