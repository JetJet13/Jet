//
// Created by Johny Georges on 2024-03-25.
//

#include "ast-function-argument-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionArgumentListNode::ASTFunctionArgumentListNode(std::shared_ptr<ASTFunctionArgumentListStartNode> functionArgumentListStartNode, std::shared_ptr<ASTFunctionArgumentListEndNode> functionArgumentListEndNode) {
    _functionArgumentListStartNode = functionArgumentListStartNode;
    _functionArgumentListEndNode = functionArgumentListEndNode;
    _children.push_back(_functionArgumentListStartNode);
    _children.push_back(_functionArgumentListEndNode);
    _commas = std::vector<std::shared_ptr<ASTCommaNode>>();
    _arguments = std::vector<std::shared_ptr<ASTFunctionArgumentNode>>();
}

ASTFunctionArgumentListNode::ASTFunctionArgumentListNode(std::shared_ptr<ASTFunctionArgumentListStartNode> functionArgumentListStartNode, std::vector<std::shared_ptr<ASTFunctionArgumentNode>> arguments, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTFunctionArgumentListEndNode> functionArgumentListEndNode) {
    _functionArgumentListStartNode = functionArgumentListStartNode;
    _functionArgumentListEndNode = functionArgumentListEndNode;
    _children.push_back(_functionArgumentListStartNode);
    _commas = commas;
    _arguments = std::vector<std::shared_ptr<ASTFunctionArgumentNode>>();
    for (auto argument: arguments) {
        this->addArgument(argument);
    }
    _children.push_back(_functionArgumentListEndNode);
}

std::vector<std::shared_ptr<ASTFunctionArgumentNode>>* ASTFunctionArgumentListNode::getArguments() {
    return &_arguments;
}

unsigned long ASTFunctionArgumentListNode::numArguments() {
    return _arguments.size();
}

std::shared_ptr<ASTFunctionArgumentListNode> ASTFunctionArgumentListNode::addArgument(std::shared_ptr<ASTFunctionArgumentNode> argument) {
    _arguments.push_back(argument);
    _children.insert(_children.end() - 1, argument);
    return std::dynamic_pointer_cast<ASTFunctionArgumentListNode>(shared_from_this());
}

std::shared_ptr<ASTFunctionArgumentListNode> ASTFunctionArgumentListNode::addComma(std::shared_ptr<ASTCommaNode> comma) {
    _commas.push_back(comma);
    return std::dynamic_pointer_cast<ASTFunctionArgumentListNode>(shared_from_this());
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

bool ASTFunctionArgumentListNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTFunctionArgumentListNode>(other);
    auto otherNodeElements = otherNode->getArguments();
    if (this->numArguments() != otherNode->numArguments()) {
        return false;
    }
    for (unsigned long i = 0; i < this->numArguments(); i++) {
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
    for (unsigned long i = 0; i < _arguments.size(); ++i) {
        sourceCodeBuilder.add(_arguments.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }
    sourceCodeBuilder.add(_functionArgumentListEndNode);
    return sourceCodeBuilder.build();
}