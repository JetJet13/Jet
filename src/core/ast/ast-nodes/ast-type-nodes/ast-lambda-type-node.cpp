//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-lambda-type-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTLambdaTypeNode::ASTLambdaTypeNode(ASTTypeParameterListNode* parameterList, std::optional<ASTTypeNode*> returnType) {
    _parameterList = parameterList;
    _returnType = returnType;
    _children.push_back(_parameterList);
    if (_returnType) {
        _children.push_back(_returnType.value());
    }
}

ASTTypeParameterListNode* ASTLambdaTypeNode::getParameterList() {
    return _parameterList;
}

std::optional<ASTTypeNode*> ASTLambdaTypeNode::getReturnType() {
    return _returnType;
}

Position* ASTLambdaTypeNode::getStartPosition() {
    return _parameterList->getStartPosition();
}

Position* ASTLambdaTypeNode::getEndPosition() {
    if (_returnType) {
        return _returnType.value()->getEndPosition();
    }
    return _parameterList->getEndPosition();
}

ASTNodeType ASTLambdaTypeNode::getNodeType() {
    return AST_LAMBDA_TYPE_NODE;
}

std::string ASTLambdaTypeNode::toString() {
    return "LAMBDA_TYPE";
}

bool ASTLambdaTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTLambdaTypeNode*)other;

    if (!_returnType.has_value() && otherNode->getReturnType().has_value() ||
        _returnType.has_value() && !otherNode->getReturnType().has_value()) {
        return false;
    }

    if (_returnType.has_value() && otherNode->getReturnType().has_value() &&
        !_returnType.value()->isSameAs(otherNode->getReturnType().value())) {
        return false;
    }

    return this->getParameterList()->isSameAs(otherNode->getParameterList());
}

void ASTLambdaTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    if (_returnType) {
        _returnType.value()->print();
    }
    Logger::log("----------");
}
