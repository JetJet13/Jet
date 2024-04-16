//
// Created by Johny Georges on 2024-04-15.
//

#ifndef JETLANG_IMPORT_MANY_MODULE_DECLARATION_REDUCER_STRATEGY_H
#define JETLANG_IMPORT_MANY_MODULE_DECLARATION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ImportManyModuleDeclarationReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_IMPORT_MANY_MODULE_DECLARATION_REDUCER_STRATEGY_H
