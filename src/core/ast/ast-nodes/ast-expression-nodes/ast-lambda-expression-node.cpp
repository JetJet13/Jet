//
// Created by Johny Georges on 2024-04-03.
//

#include "ast-lambda-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTLambdaExpressionNode::ASTLambdaExpressionNode(std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTFunctionBlockNode> block) {
    _parameters = parameters;
    _block = block;
    _typeColon = {};
    _returnType = {};
    _children.push_back(_parameters);
    _children.push_back(_block);
    _capturedValueIds = std::set<std::string>();
}

ASTLambdaExpressionNode::ASTLambdaExpressionNode(std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTFunctionBlockNode> block, std::shared_ptr<ASTTypeColonNode> typeColon, std::shared_ptr<ASTTypeNode> returnType) {
    _parameters = parameters;
    _block = block;
    _typeColon = typeColon;
    _returnType = returnType;
    _children.push_back(_parameters);
    _children.push_back(_typeColon.value());
    _children.push_back(_returnType.value());
    _children.push_back(_block);
    _capturedValueIds = std::set<std::string>();
}

Lexeme* ASTLambdaExpressionNode::getLexeme() {
    return _lexeme;
}

std::shared_ptr<ASTFunctionParameterListNode> ASTLambdaExpressionNode::getParameters() {
    return _parameters;
}

std::shared_ptr<ASTFunctionBlockNode> ASTLambdaExpressionNode::getBlock() {
    return _block;
}

std::optional<std::shared_ptr<ASTTypeNode>> ASTLambdaExpressionNode::getReturnType() {
    return _returnType;
}

std::set<std::string>* ASTLambdaExpressionNode::getCapturedValueIds() {
    return &_capturedValueIds;
}

void ASTLambdaExpressionNode::addCapturedValueId(std::string id) {
    _capturedValueIds.insert(id);
}

void ASTLambdaExpressionNode::setTypeSignature(std::shared_ptr<LambdaExpressionTypeSignature> lambdaExpressionTypeSignature) {
    _typeSignature = lambdaExpressionTypeSignature;
}

std::shared_ptr<LambdaExpressionTypeSignature> ASTLambdaExpressionNode::getLambdaTypeSignature() {
    return std::dynamic_pointer_cast<LambdaExpressionTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTLambdaExpressionNode::getTypeSignature() {
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

bool ASTLambdaExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTLambdaExpressionNode>(other);

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
        _typeColon.value()->print();
        _returnType.value()->print();
    }
    _block->print();
    Logger::log("----------");
}

std::string ASTLambdaExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_parameters);
    if (_returnType) {
        sourceCodeBuilder
        .add(_typeColon.value())
        ->add(_returnType.value());
    }
    sourceCodeBuilder.add(_block);
    return sourceCodeBuilder.build();
}