//
// Created by Johny Georges on 2026-07-11.
//

#ifndef JETLANG_SHARED_TYPE_REDUCER_STRATEGY_H
#define JETLANG_SHARED_TYPE_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class SharedTypeReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_SHARED_TYPE_REDUCER_STRATEGY_H
