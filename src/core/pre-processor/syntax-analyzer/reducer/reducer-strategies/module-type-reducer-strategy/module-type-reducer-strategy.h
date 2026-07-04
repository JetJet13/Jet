//
// Created by Johny Georges on 2026-05-30.
//

#ifndef JETLANG_MODULE_TYPE_REDUCER_STRATEGY_H
#define JETLANG_MODULE_TYPE_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ModuleTypeReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};


#endif //JETLANG_MODULE_TYPE_REDUCER_STRATEGY_H
