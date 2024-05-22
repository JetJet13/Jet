//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_AST_PROCEDURE_DECLARATION_NODE_H
#define JETLANG_AST_PROCEDURE_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-identifier-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-function-nodes/ast-function-name-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "ast-declaration-node.h"
#include "../../../type-signature/procedure-type-signature/procedure-type-signature.h"

class ASTProcedureDeclarationNode : public ASTDeclarationNode {
private:
    ASTFunctionNameNode* _name;
    ASTFunctionParameterListNode* _parameters;
    ASTFunctionBlockNode* _content;
    ProcedureTypeSignature* _typeSignature = new ProcedureTypeSignature();
public:
    explicit ASTProcedureDeclarationNode(ASTFunctionNameNode* name, ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* content);
    ASTFunctionParameterListNode* getParameters();
    ASTFunctionNameNode* getName();
    ASTFunctionBlockNode* getContent();
    unsigned long numParameters();
    void setTypeSignature(ProcedureTypeSignature* typeSignature);
    ProcedureTypeSignature* getTypeSignature() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_PROCEDURE_DECLARATION_NODE_H
