//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_LAMBDA_TYPE_REDUCER_STRATEGY_H
#define JETLANG_LAMBDA_TYPE_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class LambdaTypeReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_LAMBDA_TYPE_REDUCER_STRATEGY_H
