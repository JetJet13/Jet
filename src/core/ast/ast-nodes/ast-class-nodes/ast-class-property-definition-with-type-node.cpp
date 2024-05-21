//
// Created by Johny Georges on 2024-04-24.
//

#include "ast-class-property-definition-with-type-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTClassPropertyDefinitionWithTypeNode::ASTClassPropertyDefinitionWithTypeNode(ASTClassPropertyDefinitionNode* classPropertyDefinition, ASTTypeNode* type) {
    _classPropertyDefinition = classPropertyDefinition;
    _type = type;
    _children.push_back(_classPropertyDefinition);
    _children.push_back(_type);
}

ASTClassPropertyDefinitionNode* ASTClassPropertyDefinitionWithTypeNode::getClassPropertyDefinition() {
    return _classPropertyDefinition;
}

ASTTypeNode* ASTClassPropertyDefinitionWithTypeNode::getType() {
    return _type;
}

ASTNodeType ASTClassPropertyDefinitionWithTypeNode::getNodeType() {
    return AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE;
}

std::string ASTClassPropertyDefinitionWithTypeNode::toString() {
    return "CLASS_PROPERTY_DEFINITION_WITH_TYPE";
}

bool ASTClassPropertyDefinitionWithTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }

    auto otherNode = (ASTClassPropertyDefinitionWithTypeNode*)other;
    return this->getClassPropertyDefinition()->isSameAs(otherNode->getClassPropertyDefinition()) &&
           this->getType()->isSameAs(otherNode->getType());
}

void ASTClassPropertyDefinitionWithTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _classPropertyDefinition->print();
    _type->print();
    Logger::log("----------");
}