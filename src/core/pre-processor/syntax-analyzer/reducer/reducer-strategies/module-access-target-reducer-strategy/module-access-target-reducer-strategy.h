//
// Created by Johny Georges on 2024-11-05.
//

#ifndef JETLANG_MODULE_ACCESS_TARGET_REDUCER_STRATEGY_H
#define JETLANG_MODULE_ACCESS_TARGET_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ModuleAccessTargetReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_MODULE_ACCESS_TARGET_REDUCER_STRATEGY_H
