//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_LAMBDA_TYPE_NODE_H
#define JETLANG_AST_LAMBDA_TYPE_NODE_H

#include "ast-type-node.h"

class ASTLambdaTypeNode : public ASTTypeNode {
private:
    ASTLambdaTypeParameterListNode* _parameterList;
    ASTLambdaTypeReturnType* _returnType;
public:
    ASTLambdaTypeNode(ASTLambdaTypeParameterListNode* parameterList, ASTLambdaTypeReturnType* returnType);
    ASTLambdaTypeParameterListNode* getParameterList();
    ASTLambdaTypeReturnTypeNode* getReturnType();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_LAMBDA_TYPE_NODE_H
