//
// Created by Johny Georges on 2024-04-22.
//

#include "ast-class-property-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTClassPropertyDefinitionNode::ASTClassPropertyDefinitionNode(ASTAccessModifierNode* accessModifier, ASTClassPropertyNameNode* propertyName, bool isStatic, bool isConstant) {
    _accessModifier = accessModifier;
    _propertyName = propertyName;
    _isStatic = isStatic;
    _isConstant = isConstant;
}

ASTAccessModifierNode* ASTClassPropertyDefinitionNode::getAccessModifier() {
    return _accessModifier;
}

ASTClassPropertyNameNode* ASTClassPropertyDefinitionNode::getPropertyName() {
    return _propertyName;
}

bool ASTClassPropertyDefinitionNode::isStatic() {
    return _isStatic;
}

bool ASTClassPropertyDefinitionNode::isConstant() {
    return _isConstant;
}

ASTNodeType ASTClassPropertyDefinitionNode::getNodeType() {
    return AST_CLASS_PROPERTY_DEFINITION_NODE;
}

std::string ASTClassPropertyDefinitionNode::toString() {
    return "CLASS_PROPERTY_DEFINITION";
}

bool ASTClassPropertyDefinitionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }

    auto otherNode = (ASTClassPropertyDefinitionNode*)other;

    return this->getAccessModifier()->isSameAs(otherNode->getAccessModifier()) &&
           this->getPropertyName()->isSameAs(otherNode->getPropertyName()) &&
           this->isStatic() == otherNode->isStatic() &&
           this->isConstant() == otherNode->isConstant();
}

void ASTClassPropertyDefinitionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _accessModifier->print();
    _propertyName->print();
    Logger::log("isStatic -", _isStatic);
    Logger::log("isConstant -", _isConstant);
    Logger::log("----------");
}