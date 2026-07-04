//
// Created by Johny Georges on 2024-04-16.
//

#ifndef JETLANG_IMPORT_MODULE_LIST_SPREAD_ITEM_REDUCER_STRATEGY_H
#define JETLANG_IMPORT_MODULE_LIST_SPREAD_ITEM_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ImportModuleListSpreadItemReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_IMPORT_MODULE_LIST_SPREAD_ITEM_REDUCER_STRATEGY_H
