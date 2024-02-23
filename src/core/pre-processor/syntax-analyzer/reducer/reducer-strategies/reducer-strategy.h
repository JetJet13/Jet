//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_REDUCER_STRATEGY_H
#define JETLANG_REDUCER_STRATEGY_H

#include <optional>
#include <vector>
#include "../../../../ast/ast-nodes/ast-node.h"

class ReducerStrategy {
protected:
    bool startsWith(std::vector<ASTNode*> nodes, ASTNodeType astNodeType);
    bool endsWith(std::vector<ASTNode*> nodes, ASTNodeType astNodeType);
public:
    virtual ASTNode* execute(std::vector<ASTNode*> nodes) = 0;
};
#endif //JETLANG_REDUCER_STRATEGY_H
