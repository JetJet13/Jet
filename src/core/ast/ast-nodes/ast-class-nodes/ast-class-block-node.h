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
    std::shared_ptr<ASTBlockStartNode> _blockStartNode;
    std::shared_ptr<ASTBlockEndNode> _blockEndNode;
    std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>> _staticProperties;
    std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>> _instanceProperties;
    std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>> _properties;
    std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>> _methods;
    std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>> _staticMethods;
    std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>> _instanceMethods;
    std::vector<std::shared_ptr<ASTClassConstructorDeclarationNode>> _constructors;
public:
    ASTClassBlockNode(std::shared_ptr<ASTBlockStartNode> blockStartNode, std::vector<std::shared_ptr<ASTNode>> nodes, std::shared_ptr<ASTBlockEndNode> blockEndNode);
    ASTClassBlockNode(std::shared_ptr<ASTBlockStartNode> blockStartNode, std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>> properties, std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>> methods, std::vector<std::shared_ptr<ASTClassConstructorDeclarationNode>> constructors, std::shared_ptr<ASTBlockEndNode> blockEndNode);
    void addProperty(std::shared_ptr<ASTClassPropertyDeclarationNode> property);
    void addMethod(std::shared_ptr<ASTClassMethodDeclarationNode> method);
    void addConstructor(std::shared_ptr<ASTClassConstructorDeclarationNode> constructor);
    std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>>* getProperties();
    std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>>* getStaticProperties();
    std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>>* getInstanceProperties();
    std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>>* getMethods();
    std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>>* getStaticMethods();
    std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>>* getInstanceMethods();
    std::vector<std::shared_ptr<ASTClassConstructorDeclarationNode>>* getConstructors();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    std::string toString() override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_BLOCK_NODE_H
