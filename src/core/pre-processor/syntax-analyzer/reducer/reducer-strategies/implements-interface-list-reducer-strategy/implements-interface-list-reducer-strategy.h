//
// Created by Johny Georges on 2025-07-05.
//

#ifndef JETLANG_IMPLEMENTS_INTERFACE_LIST_REDUCER_STRATEGY_H
#define JETLANG_IMPLEMENTS_INTERFACE_LIST_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ImplementsInterfaceListReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_IMPLEMENTS_INTERFACE_LIST_REDUCER_STRATEGY_H
