//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_LAMBDA_TYPE_PARAMETER_LIST_NODE_H
#define JETLANG_AST_LAMBDA_TYPE_PARAMETER_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"

class ASTLambdaTypeParameterListNode : public ASTNode {
private:
    std::vector<ASTTypeNode*> _parameters;
public:
    ASTLambdaTypeParameterListNode();
    ASTLambdaTypeParameterListNode(std::vector<ASTTypeNode*> parameters);
    std::vector<ASTTypeNode*> getParameters();
    unsigned long numParameters();
    ASTLambdaTypeParameterListNode* addParameter(ASTTypeNode* parameter);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_LAMBDA_TYPE_PARAMETER_LIST_NODE_H
