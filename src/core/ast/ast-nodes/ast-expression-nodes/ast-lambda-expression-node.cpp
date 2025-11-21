//
// Created by Johny Georges on 2024-04-03.
//

#include "ast-lambda-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTLambdaExpressionNode::ASTLambdaExpressionNode(ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* block, std::optional<ASTTypeNode*> returnType) {
    _parameters = parameters;
    _block = block;
    _returnType = returnType;
    _children.push_back(_parameters);
    _children.push_back(_block);
    if (_returnType) {
        _children.push_back(_returnType.value());
    }
    _capturedVariables = std::vector<ASTNode*>();
}

Lexeme* ASTLambdaExpressionNode::getLexeme() {
    return _lexeme;
}

ASTFunctionParameterListNode* ASTLambdaExpressionNode::getParameters() {
    return _parameters;
}

ASTFunctionBlockNode* ASTLambdaExpressionNode::getBlock() {
    return _block;
}

std::optional<ASTTypeNode*> ASTLambdaExpressionNode::getReturnType() {
    return _returnType;
}

std::vector<ASTNode*>* ASTLambdaExpressionNode::getCapturedVariables() {
    return &_capturedVariables;
}

void ASTLambdaExpressionNode::addCapturedVariable(ASTNode* variableNode) {
    _capturedVariables.push_back(variableNode);
}

void ASTLambdaExpressionNode::setTypeSignature(LambdaExpressionTypeSignature* lambdaExpressionTypeSignature) {
    _typeSignature = lambdaExpressionTypeSignature;
}

LambdaExpressionTypeSignature* ASTLambdaExpressionNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTLambdaExpressionNode::getStartPosition() {
    return _parameters->getStartPosition();
}

Position* ASTLambdaExpressionNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTLambdaExpressionNode::getNodeType() {
    return AST_LAMBDA_EXPRESSION_NODE;
}

std::string ASTLambdaExpressionNode::toString() {
    return "LAMBDA_EXPRESSION";
}

bool ASTLambdaExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTLambdaExpressionNode*)other;

    if (!_returnType.has_value() && otherNode->getReturnType().has_value() ||
        _returnType.has_value() && !otherNode->getReturnType().has_value()) {
        return false;
    }

    if (_returnType.has_value() && otherNode->getReturnType().has_value() &&
        !_returnType.value()->isSameAs(otherNode->getReturnType().value())) {
        return false;
    }

    return this->getParameters()->isSameAs(otherNode->getParameters()) &&
           this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTLambdaExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameters->print();
    if (_returnType) {
        _returnType.value()->print();
    }
    _block->print();
    Logger::log("----------");
}

std::string ASTLambdaExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_parameters);
    if (_returnType) {
        sourceCodeBuilder.add(_returnType.value());
    }
    sourceCodeBuilder.add(_block);
    return sourceCodeBuilder.build();
}