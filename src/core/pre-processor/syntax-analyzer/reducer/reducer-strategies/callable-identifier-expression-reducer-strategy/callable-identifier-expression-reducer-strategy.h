//
// Created by Johny Georges on 2024-11-07.
//

#ifndef JETLANG_CALLABLE_IDENTIFIER_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_CALLABLE_IDENTIFIER_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class CallableIdentifierExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_CALLABLE_IDENTIFIER_EXPRESSION_REDUCER_STRATEGY_H
