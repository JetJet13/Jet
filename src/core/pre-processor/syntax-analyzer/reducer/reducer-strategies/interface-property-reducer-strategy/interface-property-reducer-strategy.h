//
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_INTERFACE_PROPERTY_REDUCER_STRATEGY_H
#define JETLANG_INTERFACE_PROPERTY_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class InterfacePropertyReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_INTERFACE_PROPERTY_REDUCER_STRATEGY_H
