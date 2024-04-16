//
// Created by Johny Georges on 2024-04-16.
//

#ifndef JETLANG_USE_MANY_MODULE_DECLARATION_REDUCER_STRATEGY_H
#define JETLANG_USE_MANY_MODULE_DECLARATION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class UseManyModuleDeclarationReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_USE_MANY_MODULE_DECLARATION_REDUCER_STRATEGY_H
