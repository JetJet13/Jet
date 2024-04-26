//
// Created by Johny Georges on 2024-04-19.
//

#ifndef JETLANG_AST_CLASS_BLOCK_NODE_H
#define JETLANG_AST_CLASS_BLOCK_NODE_H

#include "../ast-node.h"
#include "../ast-declaration-nodes/ast-class-property-declaration-node.h"
#include "../ast-declaration-nodes/ast-class-method-declaration-node.h"
#include "../ast-declaration-nodes/ast-class-constructor-declaration-node.h"

class ASTClassBlockNode : public ASTNode {
private:
    std::vector<ASTClassPropertyDeclarationNode*> _properties;
    std::vector<ASTClassMethodDeclarationNode*> _methods;
    std::vector<ASTClassConstructorDeclarationNode*> _constructors;
public:
    ASTClassBlockNode();
    ASTClassBlockNode(std::vector<ASTNode*> nodes);
    ASTClassBlockNode(std::vector<ASTClassPropertyDeclarationNode*> properties, std::vector<ASTClassMethodDeclarationNode*> methods, std::vector<ASTClassConstructorDeclarationNode*> constructors);
    void addProperty(ASTClassPropertyDeclarationNode* property);
    void addMethod(ASTClassMethodDeclarationNode* method);
    void addConstructor(ASTClassConstructorDeclarationNode* constructor);
    std::vector<ASTClassPropertyDeclarationNode*>* getProperties();
    std::vector<ASTClassMethodDeclarationNode*>* getMethods();
    std::vector<ASTClassConstructorDeclarationNode*>* getConstructors();
    ASTNodeType getNodeType() override;
    bool isSameAs(ASTNode* other) override;
    std::string toString() override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_BLOCK_NODE_H
