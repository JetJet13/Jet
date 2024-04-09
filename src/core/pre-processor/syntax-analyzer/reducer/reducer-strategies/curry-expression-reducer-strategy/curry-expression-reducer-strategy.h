//
// Created by Johny Georges on 2024-04-08.
//

#ifndef JETLANG_CURRY_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_CURRY_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class CurryExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_CURRY_EXPRESSION_REDUCER_STRATEGY_H
