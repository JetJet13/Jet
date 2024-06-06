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
#include "../ast-function-nodes/ast-function-node.h"

class ASTFunctionDeclarationNode : public ASTDeclarationNode {
private:
    ASTFunctionNode* _functionKeyword;
    ASTFunctionNameNode* _name;
    ASTFunctionParameterListNode* _parameters;
    ASTTypeNode* _returnType;
    ASTFunctionBlockNode* _block;
    FunctionTypeSignature* _typeSignature = new FunctionTypeSignature();
public:
    explicit ASTFunctionDeclarationNode(ASTFunctionNode* functionKeyword, ASTFunctionNameNode* name, ASTFunctionParameterListNode* parameters, ASTTypeNode* returnType, ASTFunctionBlockNode* content);
    ASTFunctionParameterListNode* getParameters();
    ASTFunctionNameNode* getName();
    ASTTypeNode* getReturnType();
    ASTFunctionBlockNode* getBlock();
    unsigned long numParameters();
    void setTypeSignature(FunctionTypeSignature* typeSignature);
    FunctionTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_DECLARATION_NODE_H
