//
// Created by Johny Georges on 2024-06-03.
//

#include "ast-lambda-with-fat-arrow-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTLambdaWithFatArrowExpressionNode::ASTLambdaWithFatArrowExpressionNode(std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTLambdaReturnExpressionNode> returnExpression) {
    _parameters = parameters;
    _returnExpression = returnExpression;
    _typeColon = {};
    _returnType = {};
    _capturedVariableIds = std::set<std::string>();
    _children.push_back(_parameters);
    _children.push_back(_returnExpression);
}

ASTLambdaWithFatArrowExpressionNode::ASTLambdaWithFatArrowExpressionNode(std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTLambdaReturnExpressionNode> returnExpression, std::shared_ptr<ASTTypeColonNode> typeColon, std::shared_ptr<ASTTypeNode> returnType) {
    _parameters = parameters;
    _returnExpression = returnExpression;
    _typeColon = typeColon;
    _returnType = returnType;
    _capturedVariableIds = std::set<std::string>();
    _children.push_back(_parameters);
    _children.push_back(_typeColon.value());
    _children.push_back(_returnType.value());
    _children.push_back(_returnExpression);
}

std::shared_ptr<ASTFunctionParameterListNode> ASTLambdaWithFatArrowExpressionNode::getParameters() {
    return _parameters;
}

std::shared_ptr<ASTLambdaReturnExpressionNode> ASTLambdaWithFatArrowExpressionNode::getReturnExpression() {
    return _returnExpression;
}

std::optional<std::shared_ptr<ASTTypeNode>> ASTLambdaWithFatArrowExpressionNode::getReturnType() {
    return _returnType;
}

std::set<std::string>* ASTLambdaWithFatArrowExpressionNode::getCapturedVariableIds() {
    return &_capturedVariableIds;
}

void ASTLambdaWithFatArrowExpressionNode::addCapturedValueId(std::string valueId) {
    _capturedVariableIds.insert(valueId);
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

bool ASTLambdaWithFatArrowExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTLambdaWithFatArrowExpressionNode>(other);

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
    if (_returnType) {
        _typeColon.value()->print();
        _returnType.value()->print();
    }
    _returnExpression->print();
    Logger::log("----------");
}


std::string ASTLambdaWithFatArrowExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_parameters);

    if (_returnType) {
        sourceCodeBuilder
        .add(_typeColon.value())
        ->add(_returnType.value());
    }

    sourceCodeBuilder.add(_returnExpression);
    return sourceCodeBuilder.build();
}
