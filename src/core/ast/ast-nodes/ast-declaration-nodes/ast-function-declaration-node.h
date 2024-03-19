//
// Created by Johny Georges on 2024-03-18.
//

#ifndef JETLANG_AST_FUNCTION_DECLARATION_NODE_H
#define JETLANG_AST_FUNCTION_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-block-nodes/ast-block-node.h"
#include "../ast-identifier-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"

class ASTFunctionDeclarationNode : public ASTNode {
private:
    ASTIdentifierExpressionNode* _name;
    ASTFunctionParameterListNode* _parameters;
    ASTBlockNode* _content;
public:
    explicit ASTFunctionDeclarationNode(ASTIdentifierExpressionNode* name, ASTFunctionParameterListNode* parameters, ASTBlockNode* content);
    ASTFunctionParameterListNode* getParameters();
    ASTIdentifierExpressionNode* getName();
    ASTBlockNode* getContent();
    unsigned long numParameters();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FUNCTION_DECLARATION_NODE_H
