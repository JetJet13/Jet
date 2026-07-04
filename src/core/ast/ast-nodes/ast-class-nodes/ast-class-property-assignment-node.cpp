//
// Created by Johny Georges on 2024-04-24.
//

#include "ast-class-property-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"
#include "ast-class-property-access-node.h"

ASTClassPropertyAssignmentNode::ASTClassPropertyAssignmentNode(std::shared_ptr<ASTClassPropertyAccessNode> classPropertyAccess, std::shared_ptr<ASTAssignmentOperatorNode> assignmentOperator) {
    _classPropertyAccess = classPropertyAccess;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_classPropertyAccess);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTClassAccessNode> ASTClassPropertyAssignmentNode::getClassAccess() {
    return _classPropertyAccess->getClassAccess();
}

std::shared_ptr<ASTClassPropertyNameNode> ASTClassPropertyAssignmentNode::getProperty() {
    return _classPropertyAccess->getPropertyName();
}

void ASTClassPropertyAssignmentNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTClassPropertyAssignmentNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTClassPropertyAssignmentNode::getStartPosition() {
    return _classPropertyAccess->getStartPosition();
}

Position* ASTClassPropertyAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTClassPropertyAssignmentNode::getNodeType() {
    return AST_CLASS_PROPERTY_ASSIGNMENT_NODE;
}

std::string ASTClassPropertyAssignmentNode::toString() {
    return "CLASS_PROPERTY_ASSIGNMENT";
}

bool ASTClassPropertyAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassPropertyAssignmentNode>(other);
    return this->getProperty()->isSameAs(otherNode->getProperty());
}

void ASTClassPropertyAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _classPropertyAccess->print();
    Logger::log("----------");
}

std::string ASTClassPropertyAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_classPropertyAccess)
    ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}