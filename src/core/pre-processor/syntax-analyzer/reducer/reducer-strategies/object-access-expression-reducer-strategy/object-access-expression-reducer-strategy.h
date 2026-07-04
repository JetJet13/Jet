//
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_OBJECT_ACCESS_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ObjectAccessExpressionReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_OBJECT_ACCESS_EXPRESSION_REDUCER_STRATEGY_H
