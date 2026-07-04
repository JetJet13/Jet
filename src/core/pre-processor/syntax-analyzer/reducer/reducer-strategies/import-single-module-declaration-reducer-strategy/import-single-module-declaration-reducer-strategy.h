//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_IMPORT_SINGLE_MODULE_DECLARATION_REDUCER_STRATEGY_H
#define JETLANG_IMPORT_SINGLE_MODULE_DECLARATION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ImportSingleModuleDeclarationReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};


#endif //JETLANG_IMPORT_SINGLE_MODULE_DECLARATION_REDUCER_STRATEGY_H
