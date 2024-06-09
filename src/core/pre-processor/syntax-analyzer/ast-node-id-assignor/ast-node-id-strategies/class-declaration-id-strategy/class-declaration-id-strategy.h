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
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-method-call-node.h"

class ClassDeclarationIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
private:
    std::string generateClassPropertyId(std::string className, ASTClassPropertyNameNode* classPropertyName);
    std::string generateClassMethodId(std::string className, ASTClassMethodNameNode* classMethodName);
    std::string generateClassMethodId(std::string className, ASTClassMethodCallNode* classMethodCall);
    std::string generateClassMethodId(std::string className, Lexeme* lexeme);
    std::string generateClassConstructorDeclarationId(std::string className, unsigned long constructorIndex, ASTClassConstructorDeclarationNode* constructorDeclaration);
public:
    void assign(ASTNode* node) override;
};

#endif //JETLANG_CLASS_DECLARATION_ID_STRATEGY_H
