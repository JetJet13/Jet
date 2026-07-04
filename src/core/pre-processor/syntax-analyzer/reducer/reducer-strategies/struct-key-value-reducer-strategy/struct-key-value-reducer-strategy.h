//
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_STRUCT_KEY_VALUE_REDUCER_STRATEGY_H
#define JETLANG_STRUCT_KEY_VALUE_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class StructKeyValueReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_STRUCT_KEY_VALUE_REDUCER_STRATEGY_H
