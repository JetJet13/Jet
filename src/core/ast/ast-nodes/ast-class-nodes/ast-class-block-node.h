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
    ASTBlockStartNode* _blockStartNode;
    ASTBlockEndNode* _blockEndNode;
    std::vector<ASTClassPropertyDeclarationNode*> _staticProperties;
    std::vector<ASTClassPropertyDeclarationNode*> _instanceProperties;
    std::vector<ASTClassPropertyDeclarationNode*> _properties;
    std::vector<ASTClassMethodDeclarationNode*> _methods;
    std::vector<ASTClassConstructorDeclarationNode*> _constructors;
public:
    ASTClassBlockNode(ASTBlockStartNode* blockStartNode, std::vector<ASTNode*> nodes, ASTBlockEndNode* blockEndNode);
    ASTClassBlockNode(ASTBlockStartNode* blockStartNode, std::vector<ASTClassPropertyDeclarationNode*> properties, std::vector<ASTClassMethodDeclarationNode*> methods, std::vector<ASTClassConstructorDeclarationNode*> constructors, ASTBlockEndNode* blockEndNode);
    void addProperty(ASTClassPropertyDeclarationNode* property);
    void addMethod(ASTClassMethodDeclarationNode* method);
    void addConstructor(ASTClassConstructorDeclarationNode* constructor);
    std::vector<ASTClassPropertyDeclarationNode*>* getProperties();
    std::vector<ASTClassPropertyDeclarationNode*>* getStaticProperties();
    std::vector<ASTClassPropertyDeclarationNode*>* getInstanceProperties();
    std::vector<ASTClassMethodDeclarationNode*>* getMethods();
    std::vector<ASTClassConstructorDeclarationNode*>* getConstructors();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    bool isSameAs(ASTNode* other) override;
    std::string toString() override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_BLOCK_NODE_H
