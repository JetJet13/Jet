//
// Created by Johny Georges on 2024-03-27.
//

#ifndef JETLANG_OBJECT_ACCESS_TARGET_REDUCER_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_TARGET_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ObjectAccessTargetReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};


#endif //JETLANG_OBJECT_ACCESS_TARGET_REDUCER_STRATEGY_H
