//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-type-parameter-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTypeParameterListNode::ASTTypeParameterListNode(std::shared_ptr<ASTTypeParameterListStartNode> typeParameterListStartNode, std::shared_ptr<ASTTypeParameterListEndNode> typeParameterListEndNode) {
    _typeParameterListStartNode = typeParameterListStartNode;
    _typeParameterListEndNode = typeParameterListEndNode;
    _commas = std::vector<std::shared_ptr<ASTCommaNode>>();
    _parameters = std::vector<std::shared_ptr<ASTTypeNode>>();
}

ASTTypeParameterListNode::ASTTypeParameterListNode(std::shared_ptr<ASTTypeParameterListStartNode> typeParameterListStartNode, std::vector<std::shared_ptr<ASTTypeNode>> parameters, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTTypeParameterListEndNode> typeParameterListEndNode) {
    _typeParameterListStartNode = typeParameterListStartNode;
    _typeParameterListEndNode = typeParameterListEndNode;
    _commas = commas;
    _parameters = std::vector<std::shared_ptr<ASTTypeNode>>();
    for (auto parameter: parameters) {
        _parameters.push_back(parameter);
        _children.push_back(parameter);
    }
}

std::vector<std::shared_ptr<ASTTypeNode>> ASTTypeParameterListNode::getParameters() {
    return _parameters;
}

uint64_t ASTTypeParameterListNode::numParameters() {
    return _parameters.size();
}

std::shared_ptr<ASTTypeParameterListNode> ASTTypeParameterListNode::addParameter(std::shared_ptr<ASTTypeNode> parameter) {
    _parameters.push_back(parameter);
    _children.push_back(parameter);
    return std::dynamic_pointer_cast<ASTTypeParameterListNode>(shared_from_this());
}

std::shared_ptr<ASTTypeParameterListNode> ASTTypeParameterListNode::addComma(std::shared_ptr<ASTCommaNode> comma) {
    _commas.push_back(comma);
    return std::dynamic_pointer_cast<ASTTypeParameterListNode>(shared_from_this());
}

std::shared_ptr<Position> ASTTypeParameterListNode::getStartPosition() {
    return _typeParameterListStartNode->getStartPosition();
}

std::shared_ptr<Position> ASTTypeParameterListNode::getEndPosition() {
    return _typeParameterListEndNode->getEndPosition();
}

ASTNodeType ASTTypeParameterListNode::getNodeType() {
    return AST_TYPE_PARAMETER_LIST_NODE;
}

std::string ASTTypeParameterListNode::toString() {
    return "TYPE_PARAMETER_LIST";
}

bool ASTTypeParameterListNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTypeParameterListNode>(other);
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

void ASTTypeParameterListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto parameters : _parameters) {
        parameters->print();
    }
    Logger::log("----------");
}

std::string ASTTypeParameterListNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_typeParameterListStartNode);
    for (uint64_t i = 0; i < _parameters.size(); ++i) {
        sourceCodeBuilder.add(_parameters.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }
    sourceCodeBuilder.add(_typeParameterListEndNode);
    return sourceCodeBuilder.build();
}