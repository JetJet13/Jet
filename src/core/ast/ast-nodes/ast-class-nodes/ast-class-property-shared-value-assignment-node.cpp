//
// Created by Johny Georges on 2026-02-18.
//

#include "ast-class-property-shared-value-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"
#include "ast-class-property-access-node.h"

ASTClassPropertySharedValueAssignmentNode::ASTClassPropertySharedValueAssignmentNode(std::shared_ptr<ASTClassPropertyAccessNode> classPropertyAccess, std::shared_ptr<ASTSharedValueAssignmentOperatorNode> assignmentOperator) {
    _classPropertyAccess = classPropertyAccess;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_classPropertyAccess);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTClassAccessNode> ASTClassPropertySharedValueAssignmentNode::getClassAccess() {
    return _classPropertyAccess->getClassAccess();
}

std::shared_ptr<ASTClassPropertyNameNode> ASTClassPropertySharedValueAssignmentNode::getProperty() {
    return _classPropertyAccess->getPropertyName();
}

void ASTClassPropertySharedValueAssignmentNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<TypeSignature> ASTClassPropertySharedValueAssignmentNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTClassPropertySharedValueAssignmentNode::getStartPosition() {
    return _classPropertyAccess->getStartPosition();
}

std::shared_ptr<Position> ASTClassPropertySharedValueAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTClassPropertySharedValueAssignmentNode::getNodeType() {
    return AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_NODE;
}

std::string ASTClassPropertySharedValueAssignmentNode::toString() {
    return "CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT";
}

bool ASTClassPropertySharedValueAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassPropertySharedValueAssignmentNode>(other);
    return this->getProperty()->isSameAs(otherNode->getProperty());
}

void ASTClassPropertySharedValueAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _classPropertyAccess->print();
    Logger::log("----------");
}

std::string ASTClassPropertySharedValueAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_classPropertyAccess)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}