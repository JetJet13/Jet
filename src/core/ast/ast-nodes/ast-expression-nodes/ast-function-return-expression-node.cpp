//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-return-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionReturnExpressionNode::ASTFunctionReturnExpressionNode(ASTFunctionReturnNode* returnNode, ASTExpressionNode* expressionNode) {
    _returnNode = returnNode;
    _returnExpression = expressionNode;
    _children.push_back(_returnExpression);
}

ASTFunctionReturnNode* ASTFunctionReturnExpressionNode::getReturnNode() {
    return _returnNode;
}

ASTExpressionNode* ASTFunctionReturnExpressionNode::getExpression() {
    return _returnExpression;
}

void ASTFunctionReturnExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _returnExpression->markAsGlobal();
}

Position* ASTFunctionReturnExpressionNode::getStartPosition() {
    return _returnNode->getStartPosition();
}

Position* ASTFunctionReturnExpressionNode::getEndPosition() {
    return _returnExpression->getEndPosition();
}

ASTNodeType ASTFunctionReturnExpressionNode::getNodeType() {
    return AST_FUNCTION_RETURN_EXPRESSION_NODE;
}

std::string ASTFunctionReturnExpressionNode::toString() {
    return "FUNCTION_RETURN_EXPRESSION";
}

bool ASTFunctionReturnExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFunctionReturnExpressionNode*)other;
    return this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTFunctionReturnExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _returnExpression->print();
    Logger::log("----------");
}

std::string ASTFunctionReturnExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_returnNode)
    ->addWithWhitespace(_returnExpression);
    return sourceCodeBuilder.build();
}