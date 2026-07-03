//
// Created by Johny Georges on 2026-02-18.
//

#include "ast-class-property-ref-value-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"
#include "ast-class-property-access-node.h"

ASTClassPropertyRefValueAssignmentNode::ASTClassPropertyRefValueAssignmentNode(ASTClassPropertyAccessNode* classPropertyAccess, ASTRefValueAssignmentOperatorNode* assignmentOperator) {
    _classPropertyAccess = classPropertyAccess;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_classPropertyAccess);
    _children.push_back(_assignmentOperator);
}

ASTClassAccessNode* ASTClassPropertyRefValueAssignmentNode::getClassAccess() {
    return _classPropertyAccess->getClassAccess();
}

ASTClassPropertyNameNode* ASTClassPropertyRefValueAssignmentNode::getProperty() {
    return _classPropertyAccess->getPropertyName();
}

void ASTClassPropertyRefValueAssignmentNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTClassPropertyRefValueAssignmentNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTClassPropertyRefValueAssignmentNode::getStartPosition() {
    return _classPropertyAccess->getStartPosition();
}

Position* ASTClassPropertyRefValueAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTClassPropertyRefValueAssignmentNode::getNodeType() {
    return AST_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_NODE;
}

std::string ASTClassPropertyRefValueAssignmentNode::toString() {
    return "CLASS_PROPERTY_REF_VALUE_ASSIGNMENT";
}

bool ASTClassPropertyRefValueAssignmentNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTClassPropertyRefValueAssignmentNode*)other;
    return this->getProperty()->isSameAs(otherNode->getProperty());
}

void ASTClassPropertyRefValueAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _classPropertyAccess->print();
    Logger::log("----------");
}

std::string ASTClassPropertyRefValueAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_classPropertyAccess)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}