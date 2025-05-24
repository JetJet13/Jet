//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_FOR_IN_VARIABLE_REDUCER_STRATEGY_H
#define JETLANG_FOR_IN_VARIABLE_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ForInVariableReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};


#endif //JETLANG_FOR_IN_VARIABLE_REDUCER_STRATEGY_H
