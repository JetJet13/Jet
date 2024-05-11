//
// Created by Johny Georges on 2024-04-24.
//

#include "ast-class-property-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassPropertyAssignmentNode::ASTClassPropertyAssignmentNode(ASTClassPropertyNameNode* property) {
    _property = property;
    _children.push_back(_property);
}

ASTClassPropertyNameNode* ASTClassPropertyAssignmentNode::getProperty() {
    return _property;
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
    _property->print();
    Logger::log("----------");
}