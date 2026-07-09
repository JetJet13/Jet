//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-parameter-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionParameterListNode::ASTFunctionParameterListNode(std::shared_ptr<ASTFunctionParameterListStartNode> functionParameterListStartNode, std::shared_ptr<ASTFunctionParameterListEndNode> functionParameterListEndNode) {
    _functionParameterListStartNode = functionParameterListStartNode;
    _functionParameterListEndNode = functionParameterListEndNode;
    _commas = std::vector<std::shared_ptr<ASTCommaNode>>();
    _children.push_back(_functionParameterListStartNode);
    _children.push_back(_functionParameterListEndNode);
    _parameters = std::vector<std::shared_ptr<ASTFunctionParameterNode>>();
}

ASTFunctionParameterListNode::ASTFunctionParameterListNode(std::shared_ptr<ASTFunctionParameterListStartNode> functionParameterListStartNode, std::vector<std::shared_ptr<ASTFunctionParameterNode>> parameters, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTFunctionParameterListEndNode> functionParameterListEndNode) {
    _functionParameterListStartNode = functionParameterListStartNode;
    _functionParameterListEndNode = functionParameterListEndNode;
    _children.push_back(_functionParameterListStartNode);
    _commas = commas;
    _parameters = std::vector<std::shared_ptr<ASTFunctionParameterNode>>();
    for (auto parameter: parameters) {
        this->addParameter(parameter);
    }
    _children.push_back(_functionParameterListEndNode);
}

std::vector<std::shared_ptr<ASTFunctionParameterNode>> ASTFunctionParameterListNode::getParameters() {
    return _parameters;
}

unsigned long ASTFunctionParameterListNode::numParameters() {
    return _parameters.size();
}

std::shared_ptr<ASTFunctionParameterListNode> ASTFunctionParameterListNode::addParameter(std::shared_ptr<ASTFunctionParameterNode> parameter) {
    _parameters.push_back(parameter);
    _children.insert(_children.end() - 1, parameter);
    return std::dynamic_pointer_cast<ASTFunctionParameterListNode>(shared_from_this());
}

std::shared_ptr<ASTFunctionParameterListNode> ASTFunctionParameterListNode::addComma(std::shared_ptr<ASTCommaNode> comma) {
    _commas.push_back(comma);
    return std::dynamic_pointer_cast<ASTFunctionParameterListNode>(shared_from_this());
}

void ASTFunctionParameterListNode::setTypeSignature(std::shared_ptr<ParameterListTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<ParameterListTypeSignature> ASTFunctionParameterListNode::getParameterListTypeSignature() {
    return std::dynamic_pointer_cast<ParameterListTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTFunctionParameterListNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTFunctionParameterListNode::getStartPosition() {
    return _functionParameterListStartNode->getStartPosition();
}

std::shared_ptr<Position> ASTFunctionParameterListNode::getEndPosition() {
    return _functionParameterListEndNode->getEndPosition();
}

ASTNodeType ASTFunctionParameterListNode::getNodeType() {
    return AST_FUNCTION_PARAMETER_LIST_NODE;
}

std::string ASTFunctionParameterListNode::toString() {
    return "FUNCTION_PARAMETER_LIST";
}

bool ASTFunctionParameterListNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTFunctionParameterListNode>(other);
    auto otherNodeElements = otherNode->getParameters();
    if (this->numParameters() != otherNode->numParameters()) {
        return false;
    }
    for (unsigned long i = 0; i < this->numParameters(); i++) {
        if (!_parameters[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTFunctionParameterListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto parameters : _parameters) {
        parameters->print();
    }
    Logger::log("----------");
}

std::string ASTFunctionParameterListNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_functionParameterListStartNode);
    for (unsigned long i = 0; i < _parameters.size(); ++i) {
        sourceCodeBuilder.add(_parameters.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }
    sourceCodeBuilder.add(_functionParameterListEndNode);
    return sourceCodeBuilder.build();
}