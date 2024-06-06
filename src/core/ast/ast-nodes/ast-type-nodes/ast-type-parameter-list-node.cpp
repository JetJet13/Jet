//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-type-parameter-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTypeParameterListNode::ASTTypeParameterListNode(ASTTypeParameterListStartNode* typeParameterListStartNode, ASTTypeParameterListEndNode* typeParameterListEndNode) {
    _typeParameterListStartNode = typeParameterListStartNode;
    _typeParameterListEndNode = typeParameterListEndNode;
    _parameters = std::vector<ASTTypeNode*>();
}

ASTTypeParameterListNode::ASTTypeParameterListNode(ASTTypeParameterListStartNode* typeParameterListStartNode, std::vector<ASTTypeNode*> parameters, ASTTypeParameterListEndNode* typeParameterListEndNode) {
    _typeParameterListStartNode = typeParameterListStartNode;
    _typeParameterListEndNode = typeParameterListEndNode;
    _parameters = std::vector<ASTTypeNode*>();
    for (auto parameter: parameters) {
        this->addParameter(parameter);
    }
}

std::vector<ASTTypeNode*> ASTTypeParameterListNode::getParameters() {
    return _parameters;
}

unsigned long ASTTypeParameterListNode::numParameters() {
    return _parameters.size();
}

ASTTypeParameterListNode* ASTTypeParameterListNode::addParameter(ASTTypeNode* parameter) {
    _parameters.push_back(parameter);
    _children.push_back(parameter);
    return this;
}

Position* ASTTypeParameterListNode::getStartPosition() {
    return _typeParameterListStartNode->getStartPosition();
}

Position* ASTTypeParameterListNode::getEndPosition() {
    return _typeParameterListEndNode->getEndPosition();
}

ASTNodeType ASTTypeParameterListNode::getNodeType() {
    return AST_TYPE_PARAMETER_LIST_NODE;
}

std::string ASTTypeParameterListNode::toString() {
    return "TYPE_PARAMETER_LIST";
}

bool ASTTypeParameterListNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTTypeParameterListNode*)other;
    auto otherNodeElements = otherNode->getParameters();
    if (this->numParameters() != otherNode->numParameters()) {
        return false;
    }
    for (int i = 0; i < this->numParameters(); i++) {
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
    for (auto parameters : _parameters) {
        sourceCodeBuilder.addWithWhitespace(parameters);
    }
    sourceCodeBuilder.addWithWhitespace(_typeParameterListEndNode);
    return sourceCodeBuilder.build();
}