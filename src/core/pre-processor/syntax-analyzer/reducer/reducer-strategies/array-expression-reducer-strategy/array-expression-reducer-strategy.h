//
// Created by Johny Georges on 2024-03-09.
//

#ifndef JETLANG_ARRAY_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_ARRAY_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ArrayExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_ARRAY_EXPRESSION_REDUCER_STRATEGY_H
