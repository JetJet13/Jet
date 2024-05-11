//
// Created by Johny Georges on 2024-03-25.
//

#include "ast-function-argument-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionArgumentNode::ASTFunctionArgumentNode(ASTExpressionNode* argument) {
    _argument = argument;
    _children.push_back(_argument);
}

ASTExpressionNode* ASTFunctionArgumentNode::getArgument() {
    return _argument;
}

ASTNodeType ASTFunctionArgumentNode::getNodeType() {
    return AST_FUNCTION_ARGUMENT_NODE;
}

std::string ASTFunctionArgumentNode::toString() {
    return "FUNCTION_ARGUMENT";
}

bool ASTFunctionArgumentNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTFunctionArgumentNode*)other;
    return this->getArgument()->isSameAs(otherNode->getArgument());
}

void ASTFunctionArgumentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _argument->print();
    Logger::log("----------");
}