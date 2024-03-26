//
// Created by Johny Georges on 2024-03-25.
//

#ifndef JETLANG_FUNCTION_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_FUNCTION_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class FunctionInvocationExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_FUNCTION_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H
