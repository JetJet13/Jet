//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_CONSTRUCTOR_DECLARATION_NODE_H
#define JETLANG_AST_CLASS_CONSTRUCTOR_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "ast-declaration-node.h"
#include "../ast-class-nodes/ast-constructor-node.h"
#include "../../../type-signature/class-type-signature/class-constructor-type-signature/class-constructor-type-signature.h"

class ASTClassConstructorDeclarationNode : public ASTDeclarationNode {
private:
    ASTConstructorNode* _constructor;
    ASTFunctionParameterListNode* _parameters;
    ASTFunctionBlockNode* _block;
    ClassConstructorTypeSignature* _typeSignature = new ClassConstructorTypeSignature();
public:
    explicit ASTClassConstructorDeclarationNode(ASTConstructorNode* constructor, ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* content);
    ASTConstructorNode* getConstructor();
    ASTFunctionParameterListNode* getParameters();
    ASTFunctionBlockNode* getBlock();
    unsigned long numParameters();
    void setTypeSignature(ClassConstructorTypeSignature* typeSignature);
    ClassConstructorTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_CONSTRUCTOR_DECLARATION_NODE_H
