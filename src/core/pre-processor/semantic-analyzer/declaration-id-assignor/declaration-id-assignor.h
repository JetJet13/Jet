//
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_DECLARATION_ID_ASSIGNOR_H
#define JETLANG_DECLARATION_ID_ASSIGNOR_H

#include <unordered_map>
#include "../../../token/token-table.h"
#include "../../../ast/types/ast-node-type.h"
#include "declaration-id-strategies/declaration-id-strategy.h"
#include "../../../ast/ast-nodes/ast-node.h"

class DeclarationIdAssignor {
private:
    TokenTable* _tokenTable;
    std::unordered_map<ASTNodeType, DeclarationIdStrategy*, std::hash<int>> _strategies;
    void initStrategies();
    void addStrategy(ASTNodeType astNodeType, DeclarationIdStrategy* reducerStrategy);
public:
    DeclarationIdAssignor(TokenTable* tokenTable);
    void assignId(ASTNode* node);
};

#endif //JETLANG_DECLARATION_ID_ASSIGNOR_H
