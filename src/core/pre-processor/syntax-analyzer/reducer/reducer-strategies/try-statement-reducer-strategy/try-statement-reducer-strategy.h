//
// Created by Johny Georges on 2024-04-02.
//

#ifndef JETLANG_TRY_STATEMENT_REDUCER_STRATEGY_H
#define JETLANG_TRY_STATEMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class TryStatementReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_TRY_STATEMENT_REDUCER_STRATEGY_H
