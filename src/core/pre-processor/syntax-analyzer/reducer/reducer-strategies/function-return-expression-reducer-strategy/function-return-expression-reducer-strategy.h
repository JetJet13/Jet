//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_FUNCTION_RETURN_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_FUNCTION_RETURN_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"


class FunctionReturnExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_FUNCTION_RETURN_EXPRESSION_REDUCER_STRATEGY_H
