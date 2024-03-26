//
// Created by Johny Georges on 2024-03-25.
//

#include "ast-function-argument-list-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionArgumentListNode::ASTFunctionArgumentListNode() {
    _arguments = std::vector<ASTFunctionArgumentNode*>();
}

ASTFunctionArgumentListNode::ASTFunctionArgumentListNode(std::vector<ASTFunctionArgumentNode*> arguments) {
    _arguments = std::vector<ASTFunctionArgumentNode*>();
    for (auto argument: arguments) {
        _arguments.push_back(argument);
    }
}

std::vector<ASTFunctionArgumentNode*> ASTFunctionArgumentListNode::getArguments() {
    return _arguments;
}

unsigned long ASTFunctionArgumentListNode::numArguments() {
    return _arguments.size();
}

ASTFunctionArgumentListNode* ASTFunctionArgumentListNode::addArgument(ASTFunctionArgumentNode* argument) {
    _arguments.push_back(argument);
    return this;
}

ASTNodeType ASTFunctionArgumentListNode::getNodeType() {
    return AST_FUNCTION_ARGUMENT_LIST_NODE;
}

std::string ASTFunctionArgumentListNode::toString() {
    return "FUNCTION_ARGUMENT_LIST";
}

bool ASTFunctionArgumentListNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFunctionArgumentListNode*)other;
    auto otherNodeElements = otherNode->getArguments();
    if (this->numArguments() != otherNode->numArguments()) {
        return false;
    }
    for (int i = 0; i < this->numArguments(); i++) {
        if (!_arguments[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTFunctionArgumentListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto argument : _arguments) {
        argument->print();
    }
    Logger::log("----------");
}