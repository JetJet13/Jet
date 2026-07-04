//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ClassPropertyRefValueAssignmentStatementReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_REDUCER_STRATEGY_H
