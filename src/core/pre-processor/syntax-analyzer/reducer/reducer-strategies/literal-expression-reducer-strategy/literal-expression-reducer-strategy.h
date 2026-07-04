//
// Created by Johny Georges on 2024-02-23.
//

#ifndef JETLANG_LITERAL_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_LITERAL_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class LiteralExpressionReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_LITERAL_EXPRESSION_REDUCER_STRATEGY_H
