//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_LAMBDA_TYPE_NODE_H
#define JETLANG_AST_LAMBDA_TYPE_NODE_H

#include "ast-type-node.h"
#include "../ast-lambda-nodes/ast-lambda-type-parameter-list-node.h"

class ASTLambdaTypeNode : public ASTTypeBaseNode {
private:
    ASTLambdaTypeParameterListNode* _parameterList;
    std::optional<ASTTypeNode*> _returnType;
public:
    ASTLambdaTypeNode(ASTLambdaTypeParameterListNode* parameterList, std::optional<ASTTypeNode*> returnType = {});
    ASTLambdaTypeParameterListNode* getParameterList();
    std::optional<ASTTypeNode*> getReturnType();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_LAMBDA_TYPE_NODE_H
