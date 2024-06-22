//
// Created by Johny Georges on 2024-04-24.
//

#include "ast-class-property-definition-with-type-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTClassPropertyDefinitionWithTypeNode::ASTClassPropertyDefinitionWithTypeNode(ASTClassPropertyDefinitionNode* classPropertyDefinition, ASTTypeColonNode* colon, ASTTypeNode* type) {
    _classPropertyDefinition = classPropertyDefinition;
    _colon = colon;
    _type = type;
    _children.push_back(_classPropertyDefinition);
    _children.push_back(_colon);
    _children.push_back(_type);
}

ASTClassPropertyDefinitionNode* ASTClassPropertyDefinitionWithTypeNode::getClassPropertyDefinition() {
    return _classPropertyDefinition;
}

ASTTypeColonNode* ASTClassPropertyDefinitionWithTypeNode::getColon() {
    return _colon;
}

ASTTypeNode* ASTClassPropertyDefinitionWithTypeNode::getType() {
    return _type;
}

Position* ASTClassPropertyDefinitionWithTypeNode::getStartPosition() {
    return _classPropertyDefinition->getStartPosition();
}

Position* ASTClassPropertyDefinitionWithTypeNode::getEndPosition() {
    return _type->getEndPosition();
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

std::string ASTClassPropertyDefinitionWithTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_classPropertyDefinition)
    ->addWithWhitespace(_colon)
    ->addWithWhitespace(_type);
    return sourceCodeBuilder.build();
}