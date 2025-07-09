//
// Created by Johny Georges on 2024-04-09.
//

#include "ast-array-type-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTArrayTypeNode::ASTArrayTypeNode(ASTArrayTypeStartNode* arrayStart, ASTTypeNode* elementType, ASTArrayTypeEndNode* arrayEnd) {
    _arrayStart = arrayStart;
    _elementType = elementType;
    _arrayEnd = arrayEnd;
    _children.push_back(_arrayStart);
    _children.push_back(_elementType);
    _children.push_back(_arrayEnd);
}

ASTTypeNode* ASTArrayTypeNode::getElementType() {
    return _elementType;
}

Position* ASTArrayTypeNode::getStartPosition() {
    return _arrayStart->getStartPosition();
}

Position* ASTArrayTypeNode::getEndPosition() {
    return _arrayEnd->getEndPosition();
}

ASTNodeType ASTArrayTypeNode::getNodeType() {
    return AST_ARRAY_TYPE_NODE;
}

std::string ASTArrayTypeNode::toString() {
    return "ARRAY_TYPE";
}

bool ASTArrayTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }

    auto otherNode = (ASTArrayTypeNode*)other;
    return this->getElementType()->isSameAs(otherNode->getElementType());
}

void ASTArrayTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _elementType->print();
    Logger::log("----------");
}

std::string ASTArrayTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_arrayStart)->add(_elementType)->add(_arrayEnd);
    return sourceCodeBuilder.build();
}