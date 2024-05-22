//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H
#define JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-function-parameter-node.h"
#include "../../../type-signature/parameter-list-type-signature/parameter-list-type-signature.h"

class ASTFunctionParameterListNode : public ASTNode {
private:
    std::vector<ASTFunctionParameterNode*> _parameters;
    ParameterListTypeSignature* _typeSignature = new ParameterListTypeSignature();
public:
    ASTFunctionParameterListNode();
    ASTFunctionParameterListNode(std::vector<ASTFunctionParameterNode*> parameters);
    std::vector<ASTFunctionParameterNode*> getParameters();
    unsigned long numParameters();
    ASTFunctionParameterListNode* addParameter(ASTFunctionParameterNode* parameter);
    void setTypeSignature(ParameterListTypeSignature* typeSignature);
    ParameterListTypeSignature* getTypeSignature() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H
