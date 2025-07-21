//
// Created by Johny Georges on 2025-07-21.
//

#ifndef JETLANG_PRINT_STATEMENT_REDUCER_STRATEGY_H
#define JETLANG_PRINT_STATEMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class PrintStatementReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_PRINT_STATEMENT_REDUCER_STRATEGY_H
