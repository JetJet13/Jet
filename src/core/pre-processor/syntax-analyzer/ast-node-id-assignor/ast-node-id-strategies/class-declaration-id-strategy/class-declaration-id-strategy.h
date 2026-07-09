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
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-method-call-node.h"

class ClassDeclarationIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
private:
    std::string generateClassPropertyId(std::string className, std::shared_ptr<ASTClassPropertyNameNode> classPropertyName);
    std::string generateClassMethodId(std::string className, std::shared_ptr<ASTClassMethodNameNode> classMethodName);
    std::string generateClassMethodId(std::string className, std::shared_ptr<ASTClassMethodCallNode> classMethodCall);
    std::string generateClassMethodId(std::string className, std::shared_ptr<Lexeme> lexeme);
    std::string generateClassConstructorDeclarationId(std::string className, unsigned long constructorIndex, std::shared_ptr<ASTClassConstructorDeclarationNode> constructorDeclaration);
public:
    void assign(std::shared_ptr<ASTNode> node) override;
};

#endif //JETLANG_CLASS_DECLARATION_ID_STRATEGY_H
