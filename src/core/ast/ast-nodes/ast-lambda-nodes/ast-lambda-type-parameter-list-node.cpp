//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-lambda-type-parameter-list-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTLambdaTypeParameterListNode::ASTLambdaTypeParameterListNode() {
    _parameters = std::vector<ASTTypeNode*>();
}

ASTLambdaTypeParameterListNode::ASTLambdaTypeParameterListNode(std::vector<ASTTypeNode*> parameters) {
    _parameters = std::vector<ASTTypeNode*>();
    for (auto parameter: parameters) {
        _parameters.push_back(parameter);
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
    return this;
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