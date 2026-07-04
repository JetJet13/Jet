//
// Created by Johny Georges on 2025-01-18.
//

#ifndef JETLANG_REF_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_REF_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class RefExpressionReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_REF_EXPRESSION_REDUCER_STRATEGY_H
