//
// Created by Johny Georges on 2024-04-22.
//

#include "ast-class-property-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTClassPropertyDefinitionNode::ASTClassPropertyDefinitionNode(ASTAccessModifierNode* accessModifier, ASTClassPropertyNameNode* propertyName, std::optional<ASTStaticNode*> staticKeyword, std::optional<ASTConstNode*> constKeyword) {
    _accessModifier = accessModifier;
    _propertyName = propertyName;
    _staticKeyword = staticKeyword;
    _constKeyword = constKeyword;
    _children.push_back(_accessModifier);
    _children.push_back(_propertyName);
    if (_staticKeyword){
        _children.push_back(_staticKeyword.value());
    }
    if (_constKeyword){
        _children.push_back(_constKeyword.value());
    }
}

ASTAccessModifierNode* ASTClassPropertyDefinitionNode::getAccessModifier() {
    return _accessModifier;
}

ASTClassPropertyNameNode* ASTClassPropertyDefinitionNode::getPropertyName() {
    return _propertyName;
}

std::optional<ASTStaticNode*> ASTClassPropertyDefinitionNode::getStatic() {
    return _staticKeyword;
}

std::optional<ASTConstNode*> ASTClassPropertyDefinitionNode::getConstant() {
    return _constKeyword;
}

bool ASTClassPropertyDefinitionNode::isStatic() {
    return _staticKeyword.has_value();
}

bool ASTClassPropertyDefinitionNode::isConstant() {
    return _constKeyword.has_value();
}

Position* ASTClassPropertyDefinitionNode::getStartPosition() {
    return _accessModifier->getStartPosition();
}

Position* ASTClassPropertyDefinitionNode::getEndPosition() {
    return _propertyName->getEndPosition();
}

ASTNodeType ASTClassPropertyDefinitionNode::getNodeType() {
    return AST_CLASS_PROPERTY_DEFINITION_NODE;
}

std::string ASTClassPropertyDefinitionNode::toString() {
    return "CLASS_PROPERTY_DEFINITION";
}

bool ASTClassPropertyDefinitionNode::isSameAs(ASTNode* other) {
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
    Logger::log("isStatic -", this->isStatic());
    Logger::log("isConstant -", this->isConstant());
    Logger::log("----------");
}