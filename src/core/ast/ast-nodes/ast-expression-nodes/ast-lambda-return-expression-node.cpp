//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-lambda-return-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTLambdaReturnExpressionNode::ASTLambdaReturnExpressionNode(ASTLambdaExpressionFatArrowNode* fatArrowNode, ASTExpressionNode* expressionNode) {
    _fatArrowNode = fatArrowNode;
    _returnExpression = expressionNode;
    _children.push_back(_returnExpression);
}

ASTLambdaExpressionFatArrowNode* ASTLambdaReturnExpressionNode::getFatArrowNode() {
    return _fatArrowNode;
}

ASTExpressionNode* ASTLambdaReturnExpressionNode::getExpression() {
    return _returnExpression;
}

Position* ASTLambdaReturnExpressionNode::getStartPosition() {
    return _fatArrowNode->getStartPosition();
}

Position* ASTLambdaReturnExpressionNode::getEndPosition() {
    return _returnExpression->getEndPosition();
}

ASTNodeType ASTLambdaReturnExpressionNode::getNodeType() {
    return AST_LAMBDA_RETURN_EXPRESSION_NODE;
}

std::string ASTLambdaReturnExpressionNode::toString() {
    return "LAMBDA_RETURN_EXPRESSION";
}

bool ASTLambdaReturnExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTLambdaReturnExpressionNode*)other;
    return this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTLambdaReturnExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _returnExpression->print();
    Logger::log("----------");
}

std::string ASTLambdaReturnExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_fatArrowNode)
    ->addWithWhitespace(_returnExpression);
    return sourceCodeBuilder.build();
}