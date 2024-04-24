//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-property-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTClassPropertyNode::ASTClassPropertyNode(ASTClassPropertyInitNode* propertyInit, std::optional<ASTExpressionNode*> initializer) {
    _propertyInit = propertyInit;
    _initializer = initializer;
}

ASTClassPropertyInitNode* ASTClassPropertyNode::getPropertyInit() {
    return _propertyInit;
}

ASTAccessModifierNode* ASTClassPropertyNode::getAccessModifier() {
    return _propertyInit->getAccessModifier();
}

ASTClassPropertyNameNode* ASTClassPropertyNode::getPropertyName() {
    return _propertyInit->getPropertyName();
}

std::optional<ASTTypeNode*> ASTClassPropertyNode::getType() {
    return _propertyInit->getType();
}

std::optional<ASTExpressionNode*> ASTClassPropertyNode::getInitializer() {
    return _initializer;
}

bool ASTClassPropertyNode::isStatic() {
    return _propertyInit->isStatic();
}

bool ASTClassPropertyNode::isConstant() {
    return _propertyInit->isConstant();
}

ASTNodeType ASTClassPropertyNode::getNodeType() {
    return AST_CLASS_PROPERTY_NODE;
}

std::string ASTClassPropertyNode::toString() {
    return "CLASS_PROPERTY";
}

bool ASTClassPropertyNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }

    auto otherNode = (ASTClassPropertyNode*)other;

    if (!_initializer.has_value() && otherNode->getInitializer().has_value() ||
        _initializer.has_value() && !otherNode->getInitializer().has_value()) {
        return false;
    }

    if (_initializer.has_value() && otherNode->getInitializer().has_value() &&
        !_initializer.value()->isSameAs(otherNode->getInitializer().value())) {
        return false;
    }

    return this->getPropertyInit()->isSameAs(otherNode->getPropertyInit());
}

void ASTClassPropertyNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _propertyInit->print();
    if (_initializer) {
        _initializer.value()->print();
    }
    Logger::log("----------");
}