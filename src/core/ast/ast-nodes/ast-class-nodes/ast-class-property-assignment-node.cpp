//
// Created by Johny Georges on 2024-04-24.
//

#include "ast-class-property-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"
#include "ast-class-property-access-node.h"

ASTClassPropertyAssignmentNode::ASTClassPropertyAssignmentNode(ASTClassPropertyAccessNode* classPropertyAccess, ASTAssignmentOperatorNode* assignmentOperator) {
    _classPropertyAccess = classPropertyAccess;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_classPropertyAccess);
    _children.push_back(_assignmentOperator);
}

ASTClassAccessNode* ASTClassPropertyAssignmentNode::getClassAccess() {
    return _classPropertyAccess->getClassAccess();
}

ASTClassPropertyNameNode* ASTClassPropertyAssignmentNode::getProperty() {
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

bool ASTClassPropertyAssignmentNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTClassPropertyAssignmentNode*)other;
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