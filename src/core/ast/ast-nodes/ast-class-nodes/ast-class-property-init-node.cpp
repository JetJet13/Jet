//
// Created by Johny Georges on 2024-04-22.
//

#include "ast-class-property-init-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTClassPropertyInitNode::ASTClassPropertyInitNode(ASTAccessModifierNode* accessModifier, ASTClassPropertyNameNode* propertyName, std::optional<ASTStaticNode*> staticKeyword, std::optional<ASTConstNode*> constKeyword, std::optional<ASTAssignmentOperatorNode*> assignmentOperator, std::optional<ASTTypeColonNode*> colon, std::optional<ASTTypeNode*> type) {
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
    if (_type) {
        _type.value()->print();
    }
    Logger::log("----------");
}

std::string ASTClassPropertyInitNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_accessModifier);
    if (_staticKeyword) {
        sourceCodeBuilder.addWithWhitespace(_staticKeyword.value());
    }
    if (_constKeyword) {
        sourceCodeBuilder.addWithWhitespace(_constKeyword.value());
    }

    sourceCodeBuilder.addWithWhitespace(_propertyName);

    if (_colon) {
        sourceCodeBuilder.addWithWhitespace(_colon.value());
    }
    if (_type) {
        sourceCodeBuilder.addWithWhitespace(_type.value());
    }
    if (_assignmentOperator){
        sourceCodeBuilder.addWithWhitespace(_assignmentOperator.value());
    }

    return sourceCodeBuilder.build();
}