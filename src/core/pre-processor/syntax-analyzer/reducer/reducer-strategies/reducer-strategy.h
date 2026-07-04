//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_REDUCER_STRATEGY_H
#define JETLANG_REDUCER_STRATEGY_H

#include <optional>
#include <vector>
#include "../../../../ast/ast-nodes/ast-node.h"
#include "../../../../ast/ast-nodes/ast-expression-nodes/ast-expression-node.h"

class ReducerStrategy {
public:
    virtual std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) = 0;
};
#endif //JETLANG_REDUCER_STRATEGY_H
