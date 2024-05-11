//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-parameter-list-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionParameterListNode::ASTFunctionParameterListNode() {
    _parameters = std::vector<ASTFunctionParameterNode*>();
}

ASTFunctionParameterListNode::ASTFunctionParameterListNode(std::vector<ASTFunctionParameterNode*> parameters) {
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