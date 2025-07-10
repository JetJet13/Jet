//
// Created by Johny Georges on 2025-07-09.
//

#ifndef JETLANG_LAMBDA_TYPE_PARAMETER_LIST_REDUCER_STRATEGY_H
#define JETLANG_LAMBDA_TYPE_PARAMETER_LIST_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class LambdaTypeParameterListReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_LAMBDA_TYPE_PARAMETER_LIST_REDUCER_STRATEGY_H
