//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_UNARY_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_UNARY_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include <optional>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class UnaryExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};


#endif //JETLANG_UNARY_EXPRESSION_REDUCER_STRATEGY_H
