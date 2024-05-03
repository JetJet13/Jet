//
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_DECLARATION_ID_STRATEGY_H
#define JETLANG_DECLARATION_ID_STRATEGY_H

#include "../../../../token/token-table.h"
#include "../../../../ast/ast-nodes/ast-node.h"

class DeclarationIdStrategy {
protected:
    TokenTable* _tokenTable;
public:
    DeclarationIdStrategy(TokenTable* tokenTable);
    virtual void assign(ASTNode* node) = 0;
};

#endif //JETLANG_DECLARATION_ID_STRATEGY_H
