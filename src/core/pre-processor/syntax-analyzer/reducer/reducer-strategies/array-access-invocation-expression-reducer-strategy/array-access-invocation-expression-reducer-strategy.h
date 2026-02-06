//
// Created by Johny Georges on 2026-02-06.
//

#ifndef JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ArrayAccessInvocationExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H
