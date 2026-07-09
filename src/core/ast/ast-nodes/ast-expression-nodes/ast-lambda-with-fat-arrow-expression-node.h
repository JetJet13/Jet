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
    std::shared_ptr<ASTFunctionParameterListNode> _parameters;
    std::shared_ptr<ASTLambdaReturnExpressionNode> _returnExpression;
    std::optional<std::shared_ptr<ASTTypeColonNode>> _typeColon;
    std::optional<std::shared_ptr<ASTTypeNode>> _returnType;
    std::shared_ptr<LambdaExpressionTypeSignature> _typeSignature = std::make_shared<LambdaExpressionTypeSignature>();
    std::set<std::string> _capturedVariableIds;
public:
    ASTLambdaWithFatArrowExpressionNode(std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTLambdaReturnExpressionNode> returnExpression);
    ASTLambdaWithFatArrowExpressionNode(std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTLambdaReturnExpressionNode> returnExpression, std::shared_ptr<ASTTypeColonNode> typeColon, std::shared_ptr<ASTTypeNode> returnType);
    std::shared_ptr<ASTFunctionParameterListNode> getParameters();
    std::shared_ptr<ASTLambdaReturnExpressionNode> getReturnExpression();
    std::optional<std::shared_ptr<ASTTypeNode>> getReturnType();
    std::set<std::string>* getCapturedVariableIds();
    void addCapturedValueId(std::string valueId);
    void setTypeSignature(std::shared_ptr<LambdaExpressionTypeSignature> lambdaExpressionTypeSignature);
    std::shared_ptr<LambdaExpressionTypeSignature> getLambdaTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H
