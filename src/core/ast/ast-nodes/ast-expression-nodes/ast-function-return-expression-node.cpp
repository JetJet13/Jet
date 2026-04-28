//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-return-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionReturnExpressionNode::ASTFunctionReturnExpressionNode(ASTFunctionReturnNode* returnNode) {
    _returnNode = returnNode;
    _returnExpression = {};
}

ASTFunctionReturnExpressionNode::ASTFunctionReturnExpressionNode(ASTFunctionReturnNode* returnNode, ASTExpressionNode* expressionNode) {
    _returnNode = returnNode;
    _returnExpression = expressionNode;
    _children.push_back(_returnExpression.value());
}

ASTFunctionReturnNode* ASTFunctionReturnExpressionNode::getReturnNode() {
    return _returnNode;
}

bool ASTFunctionReturnExpressionNode::hasExpression() {
    return _returnExpression.has_value();
}

std::optional<ASTExpressionNode*> ASTFunctionReturnExpressionNode::getExpression() {
    return _returnExpression;
}

Position* ASTFunctionReturnExpressionNode::getStartPosition() {
    return _returnNode->getStartPosition();
}

Position* ASTFunctionReturnExpressionNode::getEndPosition() {
    if (_returnExpression) {
        return _returnExpression.value()->getEndPosition();
    }
    return _returnNode->getEndPosition();
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
    if (this->getExpression() && otherNode->getExpression()) {
        return this->getExpression().value()->isSameAs(otherNode->getExpression().value());
    } else if (!this->getExpression() && !otherNode->getExpression()) {
        return true;
    } else {
        return false;
    }
}

void ASTFunctionReturnExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    if (_returnExpression) {
        _returnExpression.value()->print();
    } else {
        _returnNode->print();
    }
    Logger::log("----------");
}

std::string ASTFunctionReturnExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_returnNode);
    if (_returnExpression) {
        sourceCodeBuilder.add(_returnExpression.value());
    }
    return sourceCodeBuilder.build();
}