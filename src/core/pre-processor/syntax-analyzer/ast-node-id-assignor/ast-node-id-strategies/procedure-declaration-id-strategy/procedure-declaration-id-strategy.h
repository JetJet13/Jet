//
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_PROCEDURE_DECLARATION_ID_STRATEGY_H
#define JETLANG_PROCEDURE_DECLARATION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ast-node-id-strategy.h"

class ProcedureDeclarationIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
public:
    void assign(ASTNode* node) override;
};

#endif //JETLANG_PROCEDURE_DECLARATION_ID_STRATEGY_H
