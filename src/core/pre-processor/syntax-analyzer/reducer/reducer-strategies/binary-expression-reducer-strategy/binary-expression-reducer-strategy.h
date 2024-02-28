//
// Created by Johny Georges on 2024-02-19.
//

#ifndef JETLANG_BINARY_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_BINARY_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include <optional>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-expression-node.h"

class BinaryExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_BINARY_EXPRESSION_REDUCER_STRATEGY_H
