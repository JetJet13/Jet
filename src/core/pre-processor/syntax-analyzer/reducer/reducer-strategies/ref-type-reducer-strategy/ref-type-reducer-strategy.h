//
// Created by Johny Georges on 2025-02-07.
//

#ifndef JETLANG_REF_TYPE_REDUCER_STRATEGY_H
#define JETLANG_REF_TYPE_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class RefTypeReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_REF_TYPE_REDUCER_STRATEGY_H
