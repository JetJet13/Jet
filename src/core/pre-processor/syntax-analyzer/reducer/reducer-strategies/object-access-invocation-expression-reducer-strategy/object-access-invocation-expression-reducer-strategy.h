//
// Created by Johny Georges on 2025-06-16.
//

#ifndef JETLANG_OBJECT_ACCESS_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ObjectAccessInvocationExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};


#endif //JETLANG_OBJECT_ACCESS_INVOCATION_EXPRESSION_REDUCER_STRATEGY_H
