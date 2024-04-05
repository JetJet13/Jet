//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-lambda-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTLambdaTypeNode::ASTLambdaTypeNode(ASTLambdaTypeParameterListNode* parameterList, ASTTypeNode* returnType) {
    _parameterList = parameterList;
    _returnType = returnType;
}

ASTLambdaTypeParameterListNode* ASTLambdaTypeNode::getParameterList() {
    return _parameterList;
}

ASTTypeNode* ASTLambdaTypeNode::getReturnType() {
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
    return this->getParameterList()->isSameAs(otherNode->getParameterList()) &&
           this->getReturnType()->isSameAs(otherNode->getReturnType());
}

void ASTLambdaTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    _returnType->print();
    Logger::log("----------");
}