//
// Created by Johny Georges on 2025-07-09.
//

#include "ast-lambda-type-parameter-list-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTLambdaTypeParameterListNode::ASTLambdaTypeParameterListNode(std::shared_ptr<ASTLambdaTypeParameterListStartNode> startNode, std::shared_ptr<ASTLambdaTypeParameterListEndNode> endNode) {
    _startNode = startNode;
    _endNode = endNode;
    _commas = std::vector<std::shared_ptr<ASTCommaNode>>();
    _parameters = std::vector<std::shared_ptr<ASTTypeNode>>();
}

ASTLambdaTypeParameterListNode::ASTLambdaTypeParameterListNode(std::shared_ptr<ASTLambdaTypeParameterListStartNode> startNode, std::vector<std::shared_ptr<ASTTypeNode>> parameters, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTLambdaTypeParameterListEndNode> endNode) {
    _startNode = startNode;
    _endNode = endNode;
    _commas = commas;
    _parameters = std::vector<std::shared_ptr<ASTTypeNode>>();
    for (auto parameter: parameters) {
        _parameters.push_back(parameter);
        _children.push_back(parameter);
    }
}

std::vector<std::shared_ptr<ASTTypeNode>> ASTLambdaTypeParameterListNode::getParameters() {
    return _parameters;
}

uint64_t ASTLambdaTypeParameterListNode::numParameters() {
    return _parameters.size();
}

std::shared_ptr<ASTLambdaTypeParameterListNode> ASTLambdaTypeParameterListNode::addParameter(std::shared_ptr<ASTTypeNode> parameter) {
    _parameters.push_back(parameter);
    _children.push_back(parameter);
    return std::dynamic_pointer_cast<ASTLambdaTypeParameterListNode>(shared_from_this());
}

std::shared_ptr<ASTLambdaTypeParameterListNode> ASTLambdaTypeParameterListNode::addComma(std::shared_ptr<ASTCommaNode> comma) {
    _commas.push_back(comma);
    return std::dynamic_pointer_cast<ASTLambdaTypeParameterListNode>(shared_from_this());
}

std::shared_ptr<Position> ASTLambdaTypeParameterListNode::getStartPosition() {
    return _startNode->getStartPosition();
}

std::shared_ptr<Position> ASTLambdaTypeParameterListNode::getEndPosition() {
    return _endNode->getEndPosition();
}

ASTNodeType ASTLambdaTypeParameterListNode::getNodeType() {
    return AST_LAMBDA_TYPE_PARAMETER_LIST_NODE;
}

std::string ASTLambdaTypeParameterListNode::toString() {
    return "LAMBDA_TYPE_PARAMETER_LIST";
}

bool ASTLambdaTypeParameterListNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTLambdaTypeParameterListNode>(other);
    auto otherNodeElements = otherNode->getParameters();
    if (this->numParameters() != otherNode->numParameters()) {
        return false;
    }
    for (uint64_t i = 0; i < this->numParameters(); i++) {
        if (!_parameters[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTLambdaTypeParameterListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto parameters : _parameters) {
        parameters->print();
    }
    Logger::log("----------");
}

std::string ASTLambdaTypeParameterListNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_startNode);
    for (uint64_t i = 0; i < _parameters.size(); ++i) {
        sourceCodeBuilder.add(_parameters.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }
    sourceCodeBuilder.add(_endNode);
    return sourceCodeBuilder.build();
}