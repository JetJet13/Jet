//
// Created by Johny Georges on 2024-04-03.
//

#ifndef JETLANG_AST_LAMBDA_EXPRESSION_NODE_H
#define JETLANG_AST_LAMBDA_EXPRESSION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-node.h"
#include "../ast-function-nodes/ast-function-name-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../ast-function-nodes/ast-function-argument-list-node.h"
#include "../ast-function-nodes/ast-function-call-node.h"

class ASTLambdaExpressionNode : public ASTExpressionNode {
private:
    ASTFunctionParameterListNode* _parameters;
    ASTFunctionBlockNode* _block;
    std::optional<ASTTypeNode*> _returnType;
public:
    ASTLambdaExpressionNode(ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* block, std::optional<ASTTypeNode*> returnType = {});
    ASTFunctionParameterListNode* getParameters();
    ASTFunctionBlockNode* getBlock();
    std::optional<ASTTypeNode*> getReturnType();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};


#endif //JETLANG_AST_LAMBDA_EXPRESSION_NODE_H
