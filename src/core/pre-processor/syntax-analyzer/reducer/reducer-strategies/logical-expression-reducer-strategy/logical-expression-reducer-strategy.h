//
// Created by Johny Georges on 2024-02-20.
//

#ifndef JETLANG_LOGICAL_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_LOGICAL_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include <optional>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-expression-node.h"

class LogicalExpressionReducerStrategy : public ReducerStrategy {
private:
    ASTExpressionNode* createExpressionNode(ASTNode* node);
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_LOGICAL_EXPRESSION_REDUCER_STRATEGY_H
