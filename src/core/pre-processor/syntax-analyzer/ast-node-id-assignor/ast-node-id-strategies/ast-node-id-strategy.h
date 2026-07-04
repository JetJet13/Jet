//
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_AST_NODE_ID_STRATEGY_H
#define JETLANG_AST_NODE_ID_STRATEGY_H

#include "../../../../token/token-table.h"
#include "../../../../ast/ast-nodes/ast-node.h"

class ASTNodeIdStrategy {
protected:
    std::shared_ptr<TokenTable> _tokenTable;
public:
    ASTNodeIdStrategy(std::shared_ptr<TokenTable> tokenTable);
    virtual void assign(std::shared_ptr<ASTNode> node) = 0;
};

#endif //JETLANG_AST_NODE_ID_STRATEGY_H
