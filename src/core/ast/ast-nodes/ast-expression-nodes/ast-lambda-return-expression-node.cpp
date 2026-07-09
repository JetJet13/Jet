//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-lambda-return-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTLambdaReturnExpressionNode::ASTLambdaReturnExpressionNode(std::shared_ptr<ASTLambdaExpressionFatArrowNode> fatArrowNode, std::shared_ptr<ASTExpressionNode> expressionNode) {
    _fatArrowNode = fatArrowNode;
    _returnExpression = expressionNode;
    _children.push_back(_fatArrowNode);
    _children.push_back(_returnExpression);
}

std::shared_ptr<ASTLambdaExpressionFatArrowNode> ASTLambdaReturnExpressionNode::getFatArrowNode() {
    return _fatArrowNode;
}

std::shared_ptr<ASTExpressionNode> ASTLambdaReturnExpressionNode::getExpression() {
    return _returnExpression;
}

std::shared_ptr<Position> ASTLambdaReturnExpressionNode::getStartPosition() {
    return _fatArrowNode->getStartPosition();
}

std::shared_ptr<Position> ASTLambdaReturnExpressionNode::getEndPosition() {
    return _returnExpression->getEndPosition();
}

ASTNodeType ASTLambdaReturnExpressionNode::getNodeType() {
    return AST_LAMBDA_RETURN_EXPRESSION_NODE;
}

std::string ASTLambdaReturnExpressionNode::toString() {
    return "LAMBDA_RETURN_EXPRESSION";
}

bool ASTLambdaReturnExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTLambdaReturnExpressionNode>(other);
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
    ->add(_returnExpression);
    return sourceCodeBuilder.build();
}