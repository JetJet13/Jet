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
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_LITERAL_EXPRESSION_REDUCER_STRATEGY_H
