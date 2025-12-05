//
// Created by Johny Georges on 2024-06-03.
//

#include "ast-lambda-with-fat-arrow-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTLambdaWithFatArrowExpressionNode::ASTLambdaWithFatArrowExpressionNode(ASTFunctionParameterListNode* parameters, ASTLambdaReturnExpressionNode* returnExpression, std::optional<ASTTypeNode*> returnType) {
    _parameters = parameters;
    _returnExpression = returnExpression;
    _returnType = returnType;
    _capturedVariableIds = std::set<std::string>();
    _children.push_back(_parameters);
    _children.push_back(_returnExpression);
    if (_returnType) {
        _children.push_back(_returnType.value());
    }
}

ASTFunctionParameterListNode* ASTLambdaWithFatArrowExpressionNode::getParameters() {
    return _parameters;
}

ASTLambdaReturnExpressionNode* ASTLambdaWithFatArrowExpressionNode::getReturnExpression() {
    return _returnExpression;
}

void ASTLambdaWithFatArrowExpressionNode::markAsReferenced() {
    _isReferenced = true;
    _returnExpression->markAsReferenced();
}

std::optional<ASTTypeNode*> ASTLambdaWithFatArrowExpressionNode::getReturnType() {
    return _returnType;
}

std::set<std::string>* ASTLambdaWithFatArrowExpressionNode::getCapturedVariableIds() {
    return &_capturedVariableIds;
}

void ASTLambdaWithFatArrowExpressionNode::addCapturedVariableId(std::string variableId) {
    _capturedVariableIds.insert(variableId);
}

void ASTLambdaWithFatArrowExpressionNode::setTypeSignature(LambdaExpressionTypeSignature* lambdaExpressionTypeSignature) {
    _typeSignature = lambdaExpressionTypeSignature;
}

LambdaExpressionTypeSignature* ASTLambdaWithFatArrowExpressionNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTLambdaWithFatArrowExpressionNode::getStartPosition() {
    return _parameters->getStartPosition();
}

Position* ASTLambdaWithFatArrowExpressionNode::getEndPosition() {
    return _returnExpression->getEndPosition();
}

ASTNodeType ASTLambdaWithFatArrowExpressionNode::getNodeType() {
    return AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE;
}

std::string ASTLambdaWithFatArrowExpressionNode::toString() {
    return "LAMBDA_WITH_FAT_ARROW_EXPRESSION";
}

bool ASTLambdaWithFatArrowExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTLambdaWithFatArrowExpressionNode*)other;

    if (!_returnType.has_value() && otherNode->getReturnType().has_value() ||
        _returnType.has_value() && !otherNode->getReturnType().has_value()) {
        return false;
    }

    if (_returnType.has_value() && otherNode->getReturnType().has_value() &&
        !_returnType.value()->isSameAs(otherNode->getReturnType().value())) {
        return false;
    }

    return this->getParameters()->isSameAs(otherNode->getParameters()) &&
           this->getReturnExpression()->isSameAs(otherNode->getReturnExpression());
}

void ASTLambdaWithFatArrowExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameters->print();
    _returnExpression->print();
    Logger::log("----------");
}


std::string ASTLambdaWithFatArrowExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_parameters);

    if (_returnType) {
        sourceCodeBuilder.add(_returnType.value());
    }

    sourceCodeBuilder.add(_returnExpression);
    return sourceCodeBuilder.build();
}
