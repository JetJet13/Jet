//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_WHILE_STATEMENT_REDUCER_STRATEGY_H
#define JETLANG_WHILE_STATEMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class WhileStatementReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};


#endif //JETLANG_WHILE_STATEMENT_REDUCER_STRATEGY_H
