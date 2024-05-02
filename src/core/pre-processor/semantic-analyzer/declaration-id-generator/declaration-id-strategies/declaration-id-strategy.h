//
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_DECLARATION_ID_STRATEGY_H
#define JETLANG_DECLARATION_ID_STRATEGY_H

#include "../../declaration-id/declaration-id.h"
#include "../../../../token/token-table.h"
#include "../../../../ast/ast-nodes/ast-node.h"

class DeclarationIdStrategy {
protected:
    TokenTable* _tokenTable;
public:
    DeclarationIdStrategy(TokenTable* tokenTable);
    virtual DeclarationId* generate(ASTNode* node) = 0;
};

#endif //JETLANG_DECLARATION_ID_STRATEGY_H
