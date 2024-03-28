//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_CONTROL_FLOW_CONDITION_REDUCER_STRATEGY_H
#define JETLANG_CONTROL_FLOW_CONDITION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ControlFlowConditionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};


#endif //JETLANG_CONTROL_FLOW_CONDITION_REDUCER_STRATEGY_H
