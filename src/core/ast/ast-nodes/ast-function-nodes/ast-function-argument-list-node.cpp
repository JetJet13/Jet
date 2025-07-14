//
// Created by Johny Georges on 2024-03-25.
//

#include "ast-function-argument-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionArgumentListNode::ASTFunctionArgumentListNode(ASTFunctionArgumentListStartNode* functionArgumentListStartNode, ASTFunctionArgumentListEndNode* functionArgumentListEndNode) {
    _functionArgumentListStartNode = functionArgumentListStartNode;
    _functionArgumentListEndNode = functionArgumentListEndNode;
    _children.push_back(_functionArgumentListStartNode);
    _children.push_back(_functionArgumentListEndNode);
    _arguments = std::vector<ASTFunctionArgumentNode*>();
}

ASTFunctionArgumentListNode::ASTFunctionArgumentListNode(ASTFunctionArgumentListStartNode* functionArgumentListStartNode, std::vector<ASTFunctionArgumentNode*> arguments, ASTFunctionArgumentListEndNode* functionArgumentListEndNode) {
    _functionArgumentListStartNode = functionArgumentListStartNode;
    _functionArgumentListEndNode = functionArgumentListEndNode;
    _children.push_back(_functionArgumentListStartNode);
    _children.push_back(_functionArgumentListEndNode);
    _arguments = std::vector<ASTFunctionArgumentNode*>();
    for (auto argument: arguments) {
        this->addArgument(argument);
    }
}

std::vector<ASTFunctionArgumentNode*>* ASTFunctionArgumentListNode::getArguments() {
    return &_arguments;
}

unsigned long ASTFunctionArgumentListNode::numArguments() {
    return _arguments.size();
}

ASTFunctionArgumentListNode* ASTFunctionArgumentListNode::addArgument(ASTFunctionArgumentNode* argument) {
    _arguments.push_back(argument);
    _children.push_back(argument);
    return this;
}

ArgumentListTypeSignature* ASTFunctionArgumentListNode::getTypeSignature() {
    return _typeSignature;
}

void ASTFunctionArgumentListNode::setTypeSignature(ArgumentListTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

Position* ASTFunctionArgumentListNode::getStartPosition() {
    return _functionArgumentListStartNode->getStartPosition();
}

Position* ASTFunctionArgumentListNode::getEndPosition() {
    return _functionArgumentListEndNode->getEndPosition();
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
        if (!_arguments[i]->isSameAs(otherNodeElements->at(i))) {
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

std::string ASTFunctionArgumentListNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_functionArgumentListStartNode);
    for (auto argument : _arguments) {
        sourceCodeBuilder.add(argument);
    }
    sourceCodeBuilder.add(_functionArgumentListEndNode);
    return sourceCodeBuilder.build();
}