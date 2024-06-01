//
// Created by Johny Georges on 2024-06-01.
//

#ifndef JETLANG_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_REDUCER_STRATEGY_H
#define JETLANG_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ImportManyByWildcardModuleDeclarationReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};


#endif //JETLANG_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_REDUCER_STRATEGY_H
