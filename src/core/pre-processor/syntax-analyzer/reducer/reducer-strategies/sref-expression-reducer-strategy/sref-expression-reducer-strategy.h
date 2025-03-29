//
// Created by Johny Georges on 2025-03-29.
//

#ifndef JETLANG_SREF_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_SREF_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class SrefExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_SREF_EXPRESSION_REDUCER_STRATEGY_H
