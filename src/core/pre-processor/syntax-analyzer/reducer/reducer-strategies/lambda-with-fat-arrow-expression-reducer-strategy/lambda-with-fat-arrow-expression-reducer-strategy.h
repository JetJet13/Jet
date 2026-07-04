//
// Created by Johny Georges on 2024-06-04.
//

#ifndef JETLANG_LAMBDA_WITH_FAT_ARROW_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_LAMBDA_WITH_FAT_ARROW_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class LambdaWithFatArrowExpressionReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};


#endif //JETLANG_LAMBDA_WITH_FAT_ARROW_EXPRESSION_REDUCER_STRATEGY_H
