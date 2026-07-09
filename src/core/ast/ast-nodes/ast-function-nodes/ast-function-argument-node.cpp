//
// Created by Johny Georges on 2024-03-25.
//

#include "ast-function-argument-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionArgumentNode::ASTFunctionArgumentNode(std::shared_ptr<ASTExpressionNode> argument) {
    _argument = argument;
    _children.push_back(_argument);
}

std::shared_ptr<ASTExpressionNode> ASTFunctionArgumentNode::getArgument() {
    return _argument;
}

std::shared_ptr<Position> ASTFunctionArgumentNode::getStartPosition() {
    return _argument->getStartPosition();
}

std::shared_ptr<Position> ASTFunctionArgumentNode::getEndPosition() {
    return _argument->getEndPosition();
}

ASTNodeType ASTFunctionArgumentNode::getNodeType() {
    return AST_FUNCTION_ARGUMENT_NODE;
}

std::string ASTFunctionArgumentNode::toString() {
    return "FUNCTION_ARGUMENT";
}

bool ASTFunctionArgumentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTFunctionArgumentNode>(other);
    return this->getArgument()->isSameAs(otherNode->getArgument());
}

void ASTFunctionArgumentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _argument->print();
    Logger::log("----------");
}

std::string ASTFunctionArgumentNode::toSourceCode() {
    return _argument->toSourceCode();
}