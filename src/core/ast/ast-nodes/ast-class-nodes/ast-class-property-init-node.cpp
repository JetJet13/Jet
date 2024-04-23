//
// Created by Johny Georges on 2024-04-22.
//

#include "ast-class-property-init-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTClassPropertyInitNode::ASTClassPropertyInitNode(ASTAccessModifierNode* accessModifier, ASTClassPropertyNameNode* propertyName, bool isStatic, bool isConstant, std::optional<ASTTypeNode*> type) {
    _accessModifier = accessModifier;
    _propertyName = propertyName;
    _isStatic = isStatic;
    _isConstant = isConstant;
    _type = type;
}

ASTAccessModifierNode* ASTClassPropertyInitNode::getAccessModifier() {
    return _accessModifier;
}

ASTClassPropertyNameNode* ASTClassPropertyInitNode::getPropertyName() {
    return _propertyName;
}

std::optional<ASTTypeNode*> ASTClassPropertyInitNode::getType() {
    return _type;
}

bool ASTClassPropertyInitNode::isStatic() {
    return _isStatic;
}

bool ASTClassPropertyInitNode::isConstant() {
    return _isConstant;
}

ASTNodeType ASTClassPropertyInitNode::getNodeType() {
    return AST_CLASS_PROPERTY_INIT_NODE;
}

std::string ASTClassPropertyInitNode::toString() {
    return "CLASS_PROPERTY_INIT";
}

bool ASTClassPropertyInitNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }

    auto otherNode = (ASTClassPropertyInitNode*)other;

    if (!_type.has_value() && otherNode->getType().has_value() ||
        _type.has_value() && !otherNode->getType().has_value()) {
        return false;
    }

    if (_type.has_value() && otherNode->getType().has_value() &&
        !_type.value()->isSameAs(otherNode->getType().value())) {
        return false;
    }

    return this->getAccessModifier()->isSameAs(otherNode->getAccessModifier()) &&
           this->getPropertyName()->isSameAs(otherNode->getPropertyName()) &&
           this->isStatic() == otherNode->isStatic() &&
           this->isConstant() == otherNode->isConstant();
}

void ASTClassPropertyInitNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _accessModifier->print();
    _propertyName->print();
    Logger::log("isStatic -", _isStatic);
    Logger::log("isConstant -", _isConstant);
    if (_type) {
        _type.value()->print();
    }
    Logger::log("----------");
}