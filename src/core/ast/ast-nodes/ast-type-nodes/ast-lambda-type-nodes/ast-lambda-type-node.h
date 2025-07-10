//
// Created by Johny Georges on 2025-07-09.
//

#ifndef JETLANG_AST_LAMBDA_TYPE_NODE_H
#define JETLANG_AST_LAMBDA_TYPE_NODE_H

#include "../ast-type-base-node.h"
#include "../../ast-lambda-nodes/ast-lambda-type-fat-arrow-node.h"
#include "ast-lambda-type-parameter-list-node.h"

class ASTLambdaTypeNode : public ASTTypeBaseNode {
private:
    ASTLambdaTypeParameterListNode* _parameterList;
    ASTLambdaTypeFatArrowNode* _fatArrowNode;
    ASTTypeNode* _returnType;
public:
    ASTLambdaTypeNode(ASTLambdaTypeParameterListNode* parameterList, ASTLambdaTypeFatArrowNode* fatArrowNode, ASTTypeNode* returnType);
    ASTLambdaTypeParameterListNode* getParameterList();
    ASTTypeNode* getReturnType();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_LAMBDA_TYPE_NODE_H
