//
// Created by Johny Georges on 2024-05-31.
//

#ifndef JETLANG_FUNCTION_TYPE_REDUCER_STRATEGY_H
#define JETLANG_FUNCTION_TYPE_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class FunctionTypeReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_FUNCTION_TYPE_REDUCER_STRATEGY_H
