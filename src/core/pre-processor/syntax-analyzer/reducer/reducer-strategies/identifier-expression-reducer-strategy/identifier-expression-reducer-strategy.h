//
// Created by Johny Georges on 2024-02-23.
//

#ifndef JETLANG_IDENTIFIER_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_IDENTIFIER_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class IdentifierExpressionReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};


#endif //JETLANG_IDENTIFIER_EXPRESSION_REDUCER_STRATEGY_H
