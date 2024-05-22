//
// Created by Johny Georges on 2024-03-18.
//

#ifndef JETLANG_AST_FUNCTION_DECLARATION_NODE_H
#define JETLANG_AST_FUNCTION_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-identifier-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-function-nodes/ast-function-name-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "ast-declaration-node.h"
#include "../../../type-signature/function-type-signature/function-type-signature.h"

class ASTFunctionDeclarationNode : public ASTDeclarationNode {
private:
    ASTFunctionNameNode* _name;
    ASTFunctionParameterListNode* _parameters;
    ASTTypeNode* _returnType;
    ASTFunctionBlockNode* _content;
    FunctionTypeSignature* _typeSignature = new FunctionTypeSignature();
public:
    explicit ASTFunctionDeclarationNode(ASTFunctionNameNode* name, ASTFunctionParameterListNode* parameters, ASTTypeNode* returnType, ASTFunctionBlockNode* content);
    ASTFunctionParameterListNode* getParameters();
    ASTFunctionNameNode* getName();
    ASTTypeNode* getReturnType();
    ASTFunctionBlockNode* getContent();
    unsigned long numParameters();
    void setTypeSignature(FunctionTypeSignature* typeSignature);
    FunctionTypeSignature* getTypeSignature() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FUNCTION_DECLARATION_NODE_H
