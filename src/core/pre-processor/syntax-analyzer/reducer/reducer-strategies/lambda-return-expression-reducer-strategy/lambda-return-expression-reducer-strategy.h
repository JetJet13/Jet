//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_LAMBDA_RETURN_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_LAMBDA_RETURN_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"


class LambdaReturnExpressionReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_LAMBDA_RETURN_EXPRESSION_REDUCER_STRATEGY_H
