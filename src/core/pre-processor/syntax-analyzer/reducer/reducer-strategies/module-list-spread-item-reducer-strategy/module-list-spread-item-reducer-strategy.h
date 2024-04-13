//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_MODULE_LIST_SPREAD_ITEM_REDUCER_STRATEGY_H
#define JETLANG_MODULE_LIST_SPREAD_ITEM_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ModuleListSpreadItemReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_MODULE_LIST_SPREAD_ITEM_REDUCER_STRATEGY_H
