//
// Created by Johny Georges on 2024-05-20.
//

#ifndef JETLANG_THIS_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_THIS_EXPRESSION_REDUCER_STRATEGY_H

#include "../reducer-strategy.h"


class ThisExpressionReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_THIS_EXPRESSION_REDUCER_STRATEGY_H
