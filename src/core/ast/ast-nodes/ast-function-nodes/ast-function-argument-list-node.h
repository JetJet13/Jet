//
// Created by Johny Georges on 2024-03-25.
//

#ifndef JETLANG_AST_FUNCTION_ARGUMENT_LIST_NODE_H
#define JETLANG_AST_FUNCTION_ARGUMENT_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-function-parameter-node.h"
#include "ast-function-argument-node.h"
#include "ast-function-argument-list-start-node.h"
#include "ast-function-argument-list-end-node.h"
#include "../../../type-signature/argument-list-type-signature/argument-list-type-signature.h"

class ASTFunctionArgumentListNode : public ASTNode {
private:
    ASTFunctionArgumentListStartNode* _functionArgumentListStartNode;
    ASTFunctionArgumentListEndNode* _functionArgumentListEndNode;
    std::vector<ASTFunctionArgumentNode*> _arguments;
    ArgumentListTypeSignature* _typeSignature;
public:
    ASTFunctionArgumentListNode(ASTFunctionArgumentListStartNode* functionArgumentListStartNode, ASTFunctionArgumentListEndNode* functionArgumentListEndNode);
    ASTFunctionArgumentListNode(ASTFunctionArgumentListStartNode* functionArgumentListStartNode, std::vector<ASTFunctionArgumentNode*> arguments, ASTFunctionArgumentListEndNode* functionArgumentListEndNode);
    std::vector<ASTFunctionArgumentNode*>* getArguments();
    unsigned long numArguments();
    ASTFunctionArgumentListNode* addArgument(ASTFunctionArgumentNode* argument);
    ArgumentListTypeSignature* getTypeSignature() override;
    void setTypeSignature(ArgumentListTypeSignature* typeSignature);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_ARGUMENT_LIST_NODE_H
