//
// Created by Johny Georges on 2024-04-15.
//

#ifndef JETLANG_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_REDUCER_STRATEGY_H
#define JETLANG_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ImportModuleListByWildcardItemReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_REDUCER_STRATEGY_H
