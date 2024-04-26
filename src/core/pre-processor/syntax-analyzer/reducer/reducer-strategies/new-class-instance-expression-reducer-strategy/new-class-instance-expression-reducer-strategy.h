//
// Created by Johny Georges on 2024-04-26.
//

#ifndef JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class NewClassInstanceExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_REDUCER_STRATEGY_H
