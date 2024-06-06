//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H
#define JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-function-parameter-node.h"
#include "../../../type-signature/parameter-list-type-signature/parameter-list-type-signature.h"
#include "ast-function-parameter-list-start-node.h"
#include "ast-function-parameter-list-end-node.h"

class ASTFunctionParameterListNode : public ASTNode {
private:
    ASTFunctionParameterListStartNode* _functionParameterListStartNode;
    ASTFunctionParameterListEndNode* _functionParameterListEndNode;
    std::vector<ASTFunctionParameterNode*> _parameters;
    ParameterListTypeSignature* _typeSignature = new ParameterListTypeSignature();
public:
    ASTFunctionParameterListNode(ASTFunctionParameterListStartNode* functionParameterListStartNode, ASTFunctionParameterListEndNode* functionParameterListEndNode);
    ASTFunctionParameterListNode(ASTFunctionParameterListStartNode* functionParameterListStartNode, std::vector<ASTFunctionParameterNode*> parameters, ASTFunctionParameterListEndNode* functionParameterListEndNode);
    std::vector<ASTFunctionParameterNode*> getParameters();
    unsigned long numParameters();
    ASTFunctionParameterListNode* addParameter(ASTFunctionParameterNode* parameter);
    void setTypeSignature(ParameterListTypeSignature* typeSignature);
    ParameterListTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H
