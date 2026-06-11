//
// Created by Johny Georges on 2024-06-03.
//

#ifndef JETLANG_AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H
#define JETLANG_AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H

#include <set>
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
    std::optional<ASTTypeColonNode*> _typeColon;
    std::optional<ASTTypeNode*> _returnType;
    LambdaExpressionTypeSignature* _typeSignature = new LambdaExpressionTypeSignature();
    std::set<std::string> _capturedVariableIds;
public:
    ASTLambdaWithFatArrowExpressionNode(ASTFunctionParameterListNode* parameters, ASTLambdaReturnExpressionNode* returnExpression);
    ASTLambdaWithFatArrowExpressionNode(ASTFunctionParameterListNode* parameters, ASTLambdaReturnExpressionNode* returnExpression, ASTTypeColonNode* typeColon, ASTTypeNode* returnType);
    ASTFunctionParameterListNode* getParameters();
    ASTLambdaReturnExpressionNode* getReturnExpression();
    std::optional<ASTTypeNode*> getReturnType();
    std::set<std::string>* getCapturedVariableIds();
    void addCapturedValueId(std::string valueId);
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
