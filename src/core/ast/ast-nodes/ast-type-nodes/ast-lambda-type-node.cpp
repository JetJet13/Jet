//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-lambda-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTLambdaTypeNode::ASTLambdaTypeNode(ASTLambdaTypeParameterListNode* parameterList, std::optional<ASTTypeNode*> returnType) {
    _parameterList = parameterList;
    _returnType = returnType;
}

ASTLambdaTypeParameterListNode* ASTLambdaTypeNode::getParameterList() {
    return _parameterList;
}

std::optional<ASTTypeNode*> ASTLambdaTypeNode::getReturnType() {
    return _returnType;
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