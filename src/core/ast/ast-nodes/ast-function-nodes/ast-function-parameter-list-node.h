//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H
#define JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"

class ASTFunctionParameterListNode : public ASTNode {
private:
    std::vector<ASTIdentifierExpressionNode*> _parameters;
public:
    ASTFunctionParameterListNode();
    ASTFunctionParameterListNode(std::vector<ASTIdentifierExpressionNode*> parameters);
    std::vector<ASTIdentifierExpressionNode*> getParameters();
    unsigned long numParameters();
    ASTFunctionParameterListNode* addParameter(ASTIdentifierExpressionNode* parameter);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H
