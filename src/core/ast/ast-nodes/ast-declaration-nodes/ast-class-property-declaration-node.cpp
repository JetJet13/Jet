//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-property-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTClassPropertyDeclarationNode::ASTClassPropertyDeclarationNode(ASTAccessModifierNode* accessModifier, ASTClassPropertyNameNode* propertyName, bool isStatic, bool isConstant, std::optional<ASTTypeNode*> type, std::optional<ASTExpressionNode*> initializer) {
    _accessModifier = accessModifier;
    _propertyName = propertyName;
    _isStatic = isStatic;
    _isConstant = isConstant;
    _type = type;
    _initializer = initializer;
}

ASTAccessModifierNode* ASTClassPropertyDeclarationNode::getAccessModifier() {
    return _accessModifier;
}

ASTClassPropertyNameNode* ASTClassPropertyDeclarationNode::getPropertyName() {
    return _propertyName;
}

std::optional<ASTTypeNode*> ASTClassPropertyDeclarationNode::getType() {
    return _type;
}

std::optional<ASTExpressionNode*> ASTClassPropertyDeclarationNode::getInitializer() {
    return _initializer;
}

bool ASTClassPropertyDeclarationNode::isStatic() {
    return _isStatic;
}

bool ASTClassPropertyDeclarationNode::isConstant() {
    return _isConstant;
}

ASTNodeType ASTClassPropertyDeclarationNode::getNodeType() {
    return AST_CLASS_PROPERTY_DECLARATION_NODE;
}

std::string ASTClassPropertyDeclarationNode::toString() {
    return "CLASS_PROPERTY_DECLARATION";
}

bool ASTClassPropertyDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }

    auto otherNode = (ASTClassPropertyDeclarationNode*)other;

    if (!_initializer.has_value() && otherNode->getInitializer().has_value() ||
        _initializer.has_value() && !otherNode->getInitializer().has_value()) {
        return false;
    }

    if (_initializer.has_value() && otherNode->getInitializer().has_value() &&
        !_initializer.value()->isSameAs(otherNode->getInitializer().value())) {
        return false;
    }

    if (!_type.has_value() && otherNode->getInitializer().has_value() ||
        _type.has_value() && !otherNode->getInitializer().has_value()) {
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

void ASTClassPropertyDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _accessModifier->print();
    _propertyName->print();
    Logger::log("isStatic -", _isStatic);
    Logger::log("isConstant -", _isConstant);
    if (_initializer) {
        _initializer.value()->print();
    }
    Logger::log("----------");
}