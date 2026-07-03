//
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_AST_NODE_ID_ASSIGNOR_H
#define JETLANG_AST_NODE_ID_ASSIGNOR_H

#include <unordered_map>
#include "../../../token/token-table.h"
#include "../../../ast/types/ast-node-type.h"
#include "../../../ast/ast-nodes/ast-node.h"
#include "ast-node-id-strategies/ast-node-id-strategy.h"

class ASTNodeIdAssignor {
private:
    std::shared_ptr<TokenTable> _tokenTable;
    std::unordered_map<ASTNodeType, std::shared_ptr<ASTNodeIdStrategy>, std::hash<int>> _strategies;
    void initStrategies();
    void addStrategy(ASTNodeType astNodeType, std::shared_ptr<ASTNodeIdStrategy> reducerStrategy);
public:
    ASTNodeIdAssignor(std::shared_ptr<TokenTable> tokenTable);
    void assignIdIfNecessary(ASTNode* node);
};

#endif //JETLANG_AST_NODE_ID_ASSIGNOR_H
