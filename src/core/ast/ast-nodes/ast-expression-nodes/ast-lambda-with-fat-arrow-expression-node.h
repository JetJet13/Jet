//
// Created by Johny Georges on 2024-06-03.
//

#ifndef JETLANG_AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H
#define JETLANG_AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../../../type-signature/invocable-type-signature/lambda-type-signature/lambda-expression-type-signature/lambda-expression-type-signature.h"
#include "ast-lambda-return-expression-node.h"

class ASTLambdaWithFatArrowExpressionNode : public ASTExpressionNode {
private:
    ASTFunctionParameterListNode* _parameters;
    ASTLambdaReturnExpressionNode* _returnExpression;
    std::optional<ASTTypeNode*> _returnType;
    LambdaExpressionTypeSignature* _typeSignature = new LambdaExpressionTypeSignature();
    std::vector<std::string> _capturedVariableIds;
public:
    ASTLambdaWithFatArrowExpressionNode(ASTFunctionParameterListNode* parameters, ASTLambdaReturnExpressionNode* returnExpression, std::optional<ASTTypeNode*> returnType = {});
    ASTFunctionParameterListNode* getParameters();
    ASTLambdaReturnExpressionNode* getReturnExpression();
    std::optional<ASTTypeNode*> getReturnType();
    std::vector<std::string>* getCapturedVariableIds();
    void addCapturedVariableId(std::string variableId);
    void markAsReferenced() override;
    void setTypeSignature(LambdaExpressionTypeSignature* lambdaExpressionTypeSignature);
    LambdaExpressionTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H
