//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-property-access-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassPropertyAccessNode::ASTClassPropertyAccessNode(ASTClassPropertyNameNode* property) {
    _property = property;
    _children.push_back(_property);
}

ASTClassPropertyNameNode* ASTClassPropertyAccessNode::getProperty() {
    return _property;
}

ASTNodeType ASTClassPropertyAccessNode::getNodeType() {
    return AST_CLASS_PROPERTY_ACCESS_NODE;
}

std::string ASTClassPropertyAccessNode::toString() {
    return "CLASS_PROPERTY_ACCESS";
}

bool ASTClassPropertyAccessNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTClassPropertyAccessNode*)other;
    return this->getProperty()->isSameAs(otherNode->getProperty());
}

void ASTClassPropertyAccessNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _property->print();
    Logger::log("----------");
}