//
// Created by Johny Georges on 2024-04-25.
//

#ifndef JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ClassMethodInvocationExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H
