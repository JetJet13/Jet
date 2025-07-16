//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-parameter-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionParameterListNode::ASTFunctionParameterListNode(ASTFunctionParameterListStartNode* functionParameterListStartNode, ASTFunctionParameterListEndNode* functionParameterListEndNode) {
    _functionParameterListStartNode = functionParameterListStartNode;
    _functionParameterListEndNode = functionParameterListEndNode;
    _commas = std::vector<ASTCommaNode*>();
    _children.push_back(_functionParameterListStartNode);
    _children.push_back(_functionParameterListEndNode);
    _parameters = std::vector<ASTFunctionParameterNode*>();
}

ASTFunctionParameterListNode::ASTFunctionParameterListNode(ASTFunctionParameterListStartNode* functionParameterListStartNode, std::vector<ASTFunctionParameterNode*> parameters, std::vector<ASTCommaNode*> commas, ASTFunctionParameterListEndNode* functionParameterListEndNode) {
    _functionParameterListStartNode = functionParameterListStartNode;
    _functionParameterListEndNode = functionParameterListEndNode;
    _children.push_back(_functionParameterListStartNode);
    _children.push_back(_functionParameterListEndNode);
    _commas = commas;
    _parameters = std::vector<ASTFunctionParameterNode*>();
    for (auto parameter: parameters) {
        this->addParameter(parameter);
    }
}

std::vector<ASTFunctionParameterNode*> ASTFunctionParameterListNode::getParameters() {
    return _parameters;
}

unsigned long ASTFunctionParameterListNode::numParameters() {
    return _parameters.size();
}

ASTFunctionParameterListNode* ASTFunctionParameterListNode::addParameter(ASTFunctionParameterNode* parameter) {
    _parameters.push_back(parameter);
    _children.push_back(parameter);
    return this;
}

ASTFunctionParameterListNode* ASTFunctionParameterListNode::addComma(ASTCommaNode* comma) {
    _commas.push_back(comma);
    return this;
}

void ASTFunctionParameterListNode::setTypeSignature(ParameterListTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

ParameterListTypeSignature* ASTFunctionParameterListNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTFunctionParameterListNode::getStartPosition() {
    return _functionParameterListStartNode->getStartPosition();
}

Position* ASTFunctionParameterListNode::getEndPosition() {
    return _functionParameterListEndNode->getEndPosition();
}

ASTNodeType ASTFunctionParameterListNode::getNodeType() {
    return AST_FUNCTION_PARAMETER_LIST_NODE;
}

std::string ASTFunctionParameterListNode::toString() {
    return "FUNCTION_PARAMETER_LIST";
}

bool ASTFunctionParameterListNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFunctionParameterListNode*)other;
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
    for (int i = 0; i < _parameters.size(); ++i) {
        sourceCodeBuilder.add(_parameters.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }
    sourceCodeBuilder.add(_functionParameterListEndNode);
    return sourceCodeBuilder.build();
}