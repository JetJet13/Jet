//
// Created by Johny Georges on 2024-03-20.
//

#include "ast-function-parameter-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionParameterNode::ASTFunctionParameterNode(ASTIdentifierExpressionNode* identifier, ASTTypeNode* type) {
    _identifier = identifier;
    _type = type;
    _children.push_back(_identifier);
    _children.push_back(_type);
}

ASTIdentifierExpressionNode* ASTFunctionParameterNode::getIdentifier() {
    return _identifier;
}

ASTTypeNode* ASTFunctionParameterNode::getType() {
    return _type;
}

void ASTFunctionParameterNode::setTypeSignature(ParameterListItemTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

ParameterListItemTypeSignature* ASTFunctionParameterNode::getTypeSignature() {
    return _typeSignature;
}

ASTNodeType ASTFunctionParameterNode::getNodeType() {
    return AST_FUNCTION_PARAMETER_NODE;
}

std::string ASTFunctionParameterNode::toString() {
    return "FUNCTION_PARAMETER";
}

bool ASTFunctionParameterNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTFunctionParameterNode*)other;
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier()) &&
           this->getType()->isSameAs(otherNode->getType());
}

void ASTFunctionParameterNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    _type->print();
    Logger::log("----------");
}