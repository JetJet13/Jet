//
// Created by Johny Georges on 2025-07-09.
//

#include "ast-lambda-type-parameter-list-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTLambdaTypeParameterListNode::ASTLambdaTypeParameterListNode(ASTLambdaTypeParameterListStartNode* startNode, ASTLambdaTypeParameterListEndNode* endNode) {
    _startNode = startNode;
    _endNode = endNode;
    _parameters = std::vector<ASTTypeNode*>();
}

ASTLambdaTypeParameterListNode::ASTLambdaTypeParameterListNode(ASTLambdaTypeParameterListStartNode* startNode, std::vector<ASTTypeNode*> parameters, ASTLambdaTypeParameterListEndNode* endNode) {
    _startNode = startNode;
    _endNode = endNode;
    _parameters = std::vector<ASTTypeNode*>();
    for (auto parameter: parameters) {
        this->addParameter(parameter);
    }
}

std::vector<ASTTypeNode*> ASTLambdaTypeParameterListNode::getParameters() {
    return _parameters;
}

unsigned long ASTLambdaTypeParameterListNode::numParameters() {
    return _parameters.size();
}

ASTLambdaTypeParameterListNode* ASTLambdaTypeParameterListNode::addParameter(ASTTypeNode* parameter) {
    _parameters.push_back(parameter);
    _children.push_back(parameter);
    return this;
}

Position* ASTLambdaTypeParameterListNode::getStartPosition() {
    return _startNode->getStartPosition();
}

Position* ASTLambdaTypeParameterListNode::getEndPosition() {
    return _endNode->getEndPosition();
}

ASTNodeType ASTLambdaTypeParameterListNode::getNodeType() {
    return AST_LAMBDA_TYPE_PARAMETER_LIST_NODE;
}

std::string ASTLambdaTypeParameterListNode::toString() {
    return "LAMBDA_TYPE_PARAMETER_LIST";
}

bool ASTLambdaTypeParameterListNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTLambdaTypeParameterListNode*)other;
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
    for (auto parameters : _parameters) {
        sourceCodeBuilder.addWithWhitespace(parameters);
    }
    sourceCodeBuilder.addWithWhitespace(_endNode);
    return sourceCodeBuilder.build();
}