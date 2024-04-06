//
// Created by Johny Georges on 2024-04-06.
//

#ifndef JETLANG_LAMBDA_FUNCTION_TYPE_PARAMETER_LIST_REDUCER_STRATEGY_H
#define JETLANG_LAMBDA_FUNCTION_TYPE_PARAMETER_LIST_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class LambdaFunctionTypeParameterListReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_LAMBDA_FUNCTION_TYPE_PARAMETER_LIST_REDUCER_STRATEGY_H
