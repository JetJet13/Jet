//
// Created by Johny Georges on 2025-01-18.
//

#ifndef JETLANG_DREF_EXPRESSION_STRATEGY_H
#define JETLANG_DREF_EXPRESSION_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class DrefExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_DREF_EXPRESSION_STRATEGY_H
