//
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_AST_NODE_ID_STRATEGY_H
#define JETLANG_AST_NODE_ID_STRATEGY_H

#include "../../../../token/token-table.h"
#include "../../../../ast/ast-nodes/ast-node.h"

class ASTNodeIdStrategy {
protected:
    TokenTable* _tokenTable;
public:
    ASTNodeIdStrategy(TokenTable* tokenTable);
    virtual void assign(ASTNode* node) = 0;
};

#endif //JETLANG_AST_NODE_ID_STRATEGY_H
