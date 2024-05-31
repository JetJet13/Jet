//
// Created by Johny Georges on 2024-05-31.
//

#ifndef JETLANG_AST_FUNCTION_TYPE_NODE_H
#define JETLANG_AST_FUNCTION_TYPE_NODE_H

#include "ast-type-base-node.h"
#include "ast-type-parameter-list-node.h"
#include "../ast-function-nodes/ast-function-node.h"
#include "../ast-lambda-nodes/ast-lambda-type-fat-arrow-node.h"
#include "../ast-lambda-nodes/ast-function-lambda-type-parameter-list-node.h"

class ASTFunctionTypeNode : public ASTTypeBaseNode {
private:
    ASTFunctionLambdaTypeParameterListNode* _parameterList;
    ASTLambdaTypeFatArrowNode* _fatArrowNode;
    ASTTypeNode* _returnType;
public:
    ASTFunctionTypeNode(ASTFunctionLambdaTypeParameterListNode* parameterList, ASTLambdaTypeFatArrowNode* fatArrowNode, ASTTypeNode* returnType);
    ASTTypeParameterListNode* getParameterList();
    ASTTypeNode* getReturnType();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_TYPE_NODE_H
