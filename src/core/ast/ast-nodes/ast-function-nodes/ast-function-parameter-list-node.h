//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H
#define JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-function-parameter-node.h"

class ASTFunctionParameterListNode : public ASTNode {
private:
    std::vector<ASTFunctionParameterNode*> _parameters;
public:
    ASTFunctionParameterListNode();
    ASTFunctionParameterListNode(std::vector<ASTFunctionParameterNode*> parameters);
    std::vector<ASTFunctionParameterNode*> getParameters();
    unsigned long numParameters();
    ASTFunctionParameterListNode* addParameter(ASTFunctionParameterNode* parameter);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H
