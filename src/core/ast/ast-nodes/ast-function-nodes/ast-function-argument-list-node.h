//
// Created by Johny Georges on 2024-03-25.
//

#ifndef JETLANG_AST_FUNCTION_ARGUMENT_LIST_NODE_H
#define JETLANG_AST_FUNCTION_ARGUMENT_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-function-parameter-node.h"
#include "ast-function-argument-node.h"

class ASTFunctionArgumentListNode : public ASTNode {
private:
    std::vector<ASTFunctionArgumentNode*> _arguments;
public:
    ASTFunctionArgumentListNode();
    ASTFunctionArgumentListNode(std::vector<ASTFunctionArgumentNode*> arguments);
    std::vector<ASTFunctionArgumentNode*> getArguments();
    unsigned long numArguments();
    ASTFunctionArgumentListNode* addArgument(ASTFunctionArgumentNode* argument);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FUNCTION_ARGUMENT_LIST_NODE_H
