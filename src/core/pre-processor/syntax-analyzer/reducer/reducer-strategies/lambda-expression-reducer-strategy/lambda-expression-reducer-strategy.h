//
// Created by Johny Georges on 2024-04-03.
//

#ifndef JETLANG_LAMBDA_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_LAMBDA_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class LambdaExpressionReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_LAMBDA_EXPRESSION_REDUCER_STRATEGY_H
