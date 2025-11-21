//
// Created by Johny Georges on 2024-04-03.
//

#ifndef JETLANG_AST_LAMBDA_EXPRESSION_NODE_H
#define JETLANG_AST_LAMBDA_EXPRESSION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../../../type-signature/invocable-type-signature/lambda-type-signature/lambda-expression-type-signature/lambda-expression-type-signature.h"
#include "../ast-declaration-nodes/ast-variable-declaration-node.h"

class ASTLambdaExpressionNode : public ASTExpressionNode {
private:
    Lexeme* _lexeme;
    ASTFunctionParameterListNode* _parameters;
    ASTFunctionBlockNode* _block;
    std::optional<ASTTypeNode*> _returnType;
    LambdaExpressionTypeSignature* _typeSignature = new LambdaExpressionTypeSignature();
    std::vector<ASTNode*> _capturedVariables;
public:
    ASTLambdaExpressionNode(ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* block, std::optional<ASTTypeNode*> returnType = {});
    Lexeme* getLexeme();
    ASTFunctionParameterListNode* getParameters();
    ASTFunctionBlockNode* getBlock();
    std::optional<ASTTypeNode*> getReturnType();
    std::vector<ASTNode*>* getCapturedVariables();
    void addCapturedVariable(ASTNode* variableNode);
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


#endif //JETLANG_AST_LAMBDA_EXPRESSION_NODE_H
