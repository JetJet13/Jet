//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_MODULE_DECLARATION_REDUCER_STRATEGY_H
#define JETLANG_MODULE_DECLARATION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ModuleDeclarationReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_MODULE_DECLARATION_REDUCER_STRATEGY_H
