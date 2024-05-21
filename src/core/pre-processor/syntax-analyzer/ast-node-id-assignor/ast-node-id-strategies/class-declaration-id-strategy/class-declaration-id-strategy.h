//
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_CLASS_DECLARATION_ID_STRATEGY_H
#define JETLANG_CLASS_DECLARATION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ast-node-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-property-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-method-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-constructor-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"
#include "../../../../semantic-analyzer/ast-traverser/ast-traverser.h"

class ClassDeclarationIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
private:
    std::string generateClassPropertyDeclarationId(std::string className, ASTClassPropertyDeclarationNode* classPropertyDeclaration);
    std::string generateClassMethodDeclarationId(std::string className, ASTClassMethodDeclarationNode* classMethodDeclaration);
    std::string generateClassConstructorDeclarationId(std::string className, unsigned long constructorIndex, ASTClassConstructorDeclarationNode* constructorDeclaration);
public:
    void assign(ASTNode* node) override;
};

#endif //JETLANG_CLASS_DECLARATION_ID_STRATEGY_H
