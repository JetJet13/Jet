//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_UNARY_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_UNARY_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include <optional>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"
#include "../../../../../ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-unary-operator-node.h"

class UnaryExpressionReducerStrategy : public ReducerStrategy {
private:
    ASTUnaryOperatorNode* createOperatorNode(ASTNode* node);
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};


#endif //JETLANG_UNARY_EXPRESSION_REDUCER_STRATEGY_H
