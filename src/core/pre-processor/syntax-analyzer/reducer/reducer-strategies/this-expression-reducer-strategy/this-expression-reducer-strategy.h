//
// Created by Johny Georges on 2024-05-20.
//

#ifndef JETLANG_THIS_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_THIS_EXPRESSION_REDUCER_STRATEGY_H

#include "../reducer-strategy.h"


class ThisExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_THIS_EXPRESSION_REDUCER_STRATEGY_H
