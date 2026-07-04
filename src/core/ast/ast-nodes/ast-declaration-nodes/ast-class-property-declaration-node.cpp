//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-property-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTClassPropertyDeclarationNode::ASTClassPropertyDeclarationNode(std::shared_ptr<ASTClassPropertyInitNode> propertyInit, std::optional<std::shared_ptr<ASTExpressionNode>> initializer) {
    _propertyInit = propertyInit;
    _initializer = initializer;
    _children.push_back(_propertyInit);
    if (_initializer) {
        _children.push_back(_initializer.value());
    }
}

std::shared_ptr<ASTClassPropertyInitNode> ASTClassPropertyDeclarationNode::getPropertyInit() {
    return _propertyInit;
}

std::shared_ptr<ASTAccessModifierNode> ASTClassPropertyDeclarationNode::getAccessModifier() {
    return _propertyInit->getAccessModifier();
}

std::shared_ptr<ASTClassPropertyNameNode> ASTClassPropertyDeclarationNode::getPropertyName() {
    return _propertyInit->getPropertyName();
}

std::string ASTClassPropertyDeclarationNode::getNormalizedPropertyName() {
    auto propertyId = _propertyInit->getPropertyName()->getId();
    auto delimiterIndex = propertyId.find('.');
    return propertyId.substr(delimiterIndex + 1);
}

std::optional<std::shared_ptr<ASTTypeNode>> ASTClassPropertyDeclarationNode::getType() {
    return _propertyInit->getType();
}

std::optional<std::shared_ptr<ASTExpressionNode>> ASTClassPropertyDeclarationNode::getInitializer() {
    return _initializer;
}

bool ASTClassPropertyDeclarationNode::isPublic() {
    return _propertyInit->getAccessModifier()->getTypeSignature()->isPublic();
}

bool ASTClassPropertyDeclarationNode::isPrivate() {
    return _propertyInit->getAccessModifier()->getTypeSignature()->isPrivate();
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

Position* ASTClassPropertyDeclarationNode::getStartPosition() {
    return _propertyInit->getStartPosition();
}

Position* ASTClassPropertyDeclarationNode::getEndPosition() {
    if (_initializer) {
        return _initializer.value()->getEndPosition();
    }
    return _propertyInit->getEndPosition();
}

ASTNodeType ASTClassPropertyDeclarationNode::getNodeType() {
    return AST_CLASS_PROPERTY_DECLARATION_NODE;
}

std::string ASTClassPropertyDeclarationNode::toString() {
    return "CLASS_PROPERTY_DECLARATION";
}

bool ASTClassPropertyDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }

    auto otherNode = std::dynamic_pointer_cast<ASTClassPropertyDeclarationNode>(other);

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
        sourceCodeBuilder.add(_initializer.value());
    }

    return sourceCodeBuilder.build();
}