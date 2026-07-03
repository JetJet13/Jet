//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-property-access-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassPropertyAccessNode::ASTClassPropertyAccessNode(ASTClassAccessNode* classAccess, ASTClassPropertyNameNode* property) {
    _classAccess = classAccess;
    _property = property;
    _children.push_back(_classAccess);
    _children.push_back(_property);
}

ASTClassAccessNode* ASTClassPropertyAccessNode::getClassAccess() {
    return _classAccess;
}

ASTClassPropertyNameNode* ASTClassPropertyAccessNode::getPropertyName() {
    return _property;
}

Position* ASTClassPropertyAccessNode::getStartPosition() {
    return _classAccess->getStartPosition();
}

Position* ASTClassPropertyAccessNode::getEndPosition() {
    return _property->getEndPosition();
}

ASTNodeType ASTClassPropertyAccessNode::getNodeType() {
    return AST_CLASS_PROPERTY_ACCESS_NODE;
}

std::string ASTClassPropertyAccessNode::toString() {
    return "CLASS_PROPERTY_ACCESS";
}

bool ASTClassPropertyAccessNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTClassPropertyAccessNode*)other;
    return this->getPropertyName()->isSameAs(otherNode->getPropertyName());
}

void ASTClassPropertyAccessNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _property->print();
    Logger::log("----------");
}

std::string ASTClassPropertyAccessNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_classAccess)
    ->add(_property);
    return sourceCodeBuilder.build();
}