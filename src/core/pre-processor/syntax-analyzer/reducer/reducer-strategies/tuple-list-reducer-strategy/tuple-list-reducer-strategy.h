//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_TUPLE_LIST_REDUCER_STRATEGY_H
#define JETLANG_TUPLE_LIST_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class TupleListReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};



#endif //JETLANG_TUPLE_LIST_REDUCER_STRATEGY_H
