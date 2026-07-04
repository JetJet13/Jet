//
// Created by Johny Georges on 2024-04-09.
//

#ifndef JETLANG_TUPLE_TYPE_REDUCER_STRATEGY_H
#define JETLANG_TUPLE_TYPE_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class TupleTypeReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_TUPLE_TYPE_REDUCER_STRATEGY_H
