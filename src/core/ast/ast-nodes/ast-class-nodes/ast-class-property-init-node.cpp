//
// Created by Johny Georges on 2024-04-22.
//

#include "ast-class-property-init-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTClassPropertyInitNode::ASTClassPropertyInitNode(std::shared_ptr<ASTAccessModifierNode> accessModifier, std::shared_ptr<ASTClassPropertyNameNode> propertyName, std::optional<std::shared_ptr<ASTStaticNode>> staticKeyword, std::optional<std::shared_ptr<ASTConstNode>> constKeyword, std::optional<std::shared_ptr<ASTAssignmentOperatorNode>> assignmentOperator, std::optional<std::shared_ptr<ASTTypeColonNode>> colon, std::optional<std::shared_ptr<ASTTypeNode>> type) {
    _accessModifier = accessModifier;
    _propertyName = propertyName;
    _assignmentOperator = assignmentOperator;
    _staticKeyword = staticKeyword;
    _constKeyword = constKeyword;
    _colon = colon;
    _type = type;
    _children.push_back(_accessModifier);
    _children.push_back(propertyName);
    if (_type) {
        _children.push_back(_type.value());
    }
}

std::shared_ptr<ASTAccessModifierNode> ASTClassPropertyInitNode::getAccessModifier() {
    return _accessModifier;
}

std::shared_ptr<ASTClassPropertyNameNode> ASTClassPropertyInitNode::getPropertyName() {
    return _propertyName;
}

std::optional<std::shared_ptr<ASTTypeNode>> ASTClassPropertyInitNode::getType() {
    return _type;
}

bool ASTClassPropertyInitNode::isStatic() {
    return _staticKeyword.has_value();
}

bool ASTClassPropertyInitNode::isConstant() {
    return _constKeyword.has_value();
}

Position* ASTClassPropertyInitNode::getStartPosition() {
    return _accessModifier->getStartPosition();
}

Position* ASTClassPropertyInitNode::getEndPosition() {
    if (_type) {
        return _type.value()->getEndPosition();
    }
    return _propertyName->getEndPosition();
}

ASTNodeType ASTClassPropertyInitNode::getNodeType() {
    return AST_CLASS_PROPERTY_INIT_NODE;
}

std::string ASTClassPropertyInitNode::toString() {
    return "CLASS_PROPERTY_INIT";
}

bool ASTClassPropertyInitNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }

    auto otherNode = std::dynamic_pointer_cast<ASTClassPropertyInitNode>(other);

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
    if (_type) {
        _type.value()->print();
    }
    Logger::log("----------");
}

std::string ASTClassPropertyInitNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_accessModifier);
    if (_staticKeyword) {
        sourceCodeBuilder.add(_staticKeyword.value());
    }
    if (_constKeyword) {
        sourceCodeBuilder.add(_constKeyword.value());
    }

    sourceCodeBuilder.add(_propertyName);

    if (_colon) {
        sourceCodeBuilder.add(_colon.value());
    }
    if (_type) {
        sourceCodeBuilder.add(_type.value());
    }
    if (_assignmentOperator){
        sourceCodeBuilder.add(_assignmentOperator.value());
    }

    return sourceCodeBuilder.build();
}