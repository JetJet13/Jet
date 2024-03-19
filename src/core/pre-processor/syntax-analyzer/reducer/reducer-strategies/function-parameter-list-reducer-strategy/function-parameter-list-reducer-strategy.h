//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_FUNCTION_PARAMETER_LIST_REDUCER_STRATEGY_H
#define JETLANG_FUNCTION_PARAMETER_LIST_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class FunctionParameterListReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_FUNCTION_PARAMETER_LIST_REDUCER_STRATEGY_H
