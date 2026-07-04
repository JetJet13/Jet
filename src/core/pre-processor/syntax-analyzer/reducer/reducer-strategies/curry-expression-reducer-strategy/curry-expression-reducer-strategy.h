//
// Created by Johny Georges on 2024-04-08.
//

#ifndef JETLANG_CURRY_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_CURRY_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class CurryExpressionReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_CURRY_EXPRESSION_REDUCER_STRATEGY_H
