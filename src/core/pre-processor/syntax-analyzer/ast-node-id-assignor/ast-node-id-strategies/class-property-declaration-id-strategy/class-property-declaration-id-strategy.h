//
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_CLASS_PROPERTY_DECLARATION_ID_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_DECLARATION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ast-node-id-strategy.h"

class ClassPropertyDeclarationIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
public:
    void assign(ASTNode* node) override;
};


#endif //JETLANG_CLASS_PROPERTY_DECLARATION_ID_STRATEGY_H
