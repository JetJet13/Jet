//
// Created by Johny Georges on 2025-06-28.
//

#ifndef JETLANG_STRUCT_TYPE_REDUCER_STRATEGY_H
#define JETLANG_STRUCT_TYPE_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class StructTypeReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};


#endif //JETLANG_STRUCT_TYPE_REDUCER_STRATEGY_H
