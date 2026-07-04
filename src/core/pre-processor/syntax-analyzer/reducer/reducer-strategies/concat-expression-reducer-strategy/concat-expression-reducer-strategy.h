//
// Created by Johny Georges on 2025-06-07.
//

#ifndef JETLANG_CONCAT_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_CONCAT_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include <optional>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-expression-node.h"

class ConcatExpressionReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_CONCAT_EXPRESSION_REDUCER_STRATEGY_H
