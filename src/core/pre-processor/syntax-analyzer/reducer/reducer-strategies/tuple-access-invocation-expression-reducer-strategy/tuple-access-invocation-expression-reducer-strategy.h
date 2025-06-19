//
// Created by Johny Georges on 2025-06-18.
//

#ifndef JETLANG_TUPLE_ACCESS_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_TUPLE_ACCESS_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class TupleAccessInvocationExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_TUPLE_ACCESS_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H
