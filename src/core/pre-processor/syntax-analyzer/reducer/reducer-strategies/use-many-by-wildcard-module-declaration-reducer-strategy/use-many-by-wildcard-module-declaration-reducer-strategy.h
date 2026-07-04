//
// Created by Johny Georges on 2024-06-04.
//

#ifndef JETLANG_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_REDUCER_STRATEGY_H
#define JETLANG_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class UseManyByWildcardModuleDeclarationReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_REDUCER_STRATEGY_H
