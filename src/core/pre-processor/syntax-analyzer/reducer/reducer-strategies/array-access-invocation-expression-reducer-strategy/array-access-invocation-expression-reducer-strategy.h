//
// Created by Johny Georges on 2026-02-06.
//

#ifndef JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ArrayAccessInvocationExpressionReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H
