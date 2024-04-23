//
// Created by Johny Georges on 2024-04-19.
//

#ifndef JETLANG_AST_CLASS_BLOCK_NODE_H
#define JETLANG_AST_CLASS_BLOCK_NODE_H

#include "../ast-node.h"
#include "ast-class-property-node.h"
#include "ast-class-method-node.h"
#include "ast-class-constructor-node.h"

class ASTClassBlockNode : public ASTNode {
private:
    std::vector<ASTClassPropertyNode*> _properties;
    std::vector<ASTClassMethodNode*> _methods;
    std::vector<ASTClassConstructorNode*> _constructors;
public:
    ASTClassBlockNode();
    ASTClassBlockNode(std::vector<ASTClassPropertyNode*> properties, std::vector<ASTClassMethodNode*> methods, std::vector<ASTClassConstructorNode*> constructors);
    void addProperty(ASTClassPropertyNode* property);
    void addMethod(ASTClassMethodNode* method);
    void addConstructor(ASTClassConstructorNode* constructor);
    std::vector<ASTClassPropertyNode*>* getProperties();
    std::vector<ASTClassMethodNode*>* getMethods();
    std::vector<ASTClassConstructorNode*>* getConstructors();
    ASTNodeType getNodeType() override;
    bool isSameAs(ASTNode* other) override;
    std::string toString() override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_BLOCK_NODE_H
