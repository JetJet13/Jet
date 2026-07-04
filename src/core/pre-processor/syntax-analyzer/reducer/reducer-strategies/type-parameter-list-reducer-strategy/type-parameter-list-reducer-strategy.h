//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_TYPE_PARAMETER_LIST_REDUCER_STRATEGY_H
#define JETLANG_TYPE_PARAMETER_LIST_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class TypeParameterListReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_TYPE_PARAMETER_LIST_REDUCER_STRATEGY_H
