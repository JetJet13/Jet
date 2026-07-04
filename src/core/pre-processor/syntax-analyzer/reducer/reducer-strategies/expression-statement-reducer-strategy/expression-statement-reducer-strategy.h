//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_EXPRESSION_STATEMENT_REDUCER_STRATEGY_H
#define JETLANG_EXPRESSION_STATEMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ExpressionStatementReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_EXPRESSION_STATEMENT_REDUCER_STRATEGY_H
