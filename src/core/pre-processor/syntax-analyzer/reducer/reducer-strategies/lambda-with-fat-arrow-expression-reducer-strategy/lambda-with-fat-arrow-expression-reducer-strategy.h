//
// Created by Johny Georges on 2024-06-04.
//

#ifndef JETLANG_LAMBDA_WITH_FAT_ARROW_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_LAMBDA_WITH_FAT_ARROW_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class LambdaWithFatArrowExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};


#endif //JETLANG_LAMBDA_WITH_FAT_ARROW_EXPRESSION_REDUCER_STRATEGY_H
