//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-property-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTClassPropertyDeclarationNode::ASTClassPropertyDeclarationNode(ASTClassPropertyInitNode* propertyInit, std::optional<ASTExpressionNode*> initializer) {
    _propertyInit = propertyInit;
    _initializer = initializer;
    _children.push_back(_propertyInit);
    if (_initializer) {
        _children.push_back(_initializer.value());
    }
}

ASTClassPropertyInitNode* ASTClassPropertyDeclarationNode::getPropertyInit() {
    return _propertyInit;
}

ASTAccessModifierNode* ASTClassPropertyDeclarationNode::getAccessModifier() {
    return _propertyInit->getAccessModifier();
}

ASTClassPropertyNameNode* ASTClassPropertyDeclarationNode::getPropertyName() {
    return _propertyInit->getPropertyName();
}

std::optional<ASTTypeNode*> ASTClassPropertyDeclarationNode::getType() {
    return _propertyInit->getType();
}

std::optional<ASTExpressionNode*> ASTClassPropertyDeclarationNode::getInitializer() {
    return _initializer;
}

bool ASTClassPropertyDeclarationNode::isStatic() {
    return _propertyInit->isStatic();
}

bool ASTClassPropertyDeclarationNode::isConstant() {
    return _propertyInit->isConstant();
}

void ASTClassPropertyDeclarationNode::setTypeSignature(ClassPropertyTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

ClassPropertyTypeSignature* ASTClassPropertyDeclarationNode::getTypeSignature() {
    return _typeSignature;
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

    return this->getPropertyInit()->isSameAs(otherNode->getPropertyInit());
}

void ASTClassPropertyDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _propertyInit->print();
    if (_initializer) {
        _initializer.value()->print();
    }
    Logger::log("----------");
}

std::string ASTClassPropertyDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_propertyInit);

    if (_initializer) {
        sourceCodeBuilder.addWithWhitespace(_initializer.value());
    }

    return sourceCodeBuilder.build();
}