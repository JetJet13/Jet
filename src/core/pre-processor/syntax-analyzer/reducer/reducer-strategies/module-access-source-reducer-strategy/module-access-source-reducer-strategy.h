//
// Created by Johny Georges on 2024-11-05.
//

#ifndef JETLANG_MODULE_ACCESS_SOURCE_REDUCER_STRATEGY_H
#define JETLANG_MODULE_ACCESS_SOURCE_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ModuleAccessSourceReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_MODULE_ACCESS_SOURCE_REDUCER_STRATEGY_H
