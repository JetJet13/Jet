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
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_TUPLE_TYPE_REDUCER_STRATEGY_H
