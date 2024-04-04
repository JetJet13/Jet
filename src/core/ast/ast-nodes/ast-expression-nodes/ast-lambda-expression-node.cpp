//
// Created by Johny Georges on 2024-04-03.
//

#include "ast-lambda-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTLambdaExpressionNode::ASTLambdaExpressionNode(ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* block, std::optional<ASTTypeNode*> returnType) {
    _parameters = parameters;
    _block = block;
    _returnType = returnType;
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