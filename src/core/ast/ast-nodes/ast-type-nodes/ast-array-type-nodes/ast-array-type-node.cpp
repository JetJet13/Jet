//
// Created by Johny Georges on 2024-04-09.
//

#include "ast-array-type-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTArrayTypeNode::ASTArrayTypeNode(std::shared_ptr<ASTArrayTypeStartNode> arrayStart, std::shared_ptr<ASTTypeNode> elementType, std::shared_ptr<ASTArrayTypeEndNode> arrayEnd) {
    _arrayStart = arrayStart;
    _elementType = elementType;
    _arrayEnd = arrayEnd;
    _children.push_back(_arrayStart);
    _children.push_back(_elementType);
    _children.push_back(_arrayEnd);
}

std::shared_ptr<ASTTypeNode> ASTArrayTypeNode::getElementType() {
    return _elementType;
}

std::shared_ptr<Position> ASTArrayTypeNode::getStartPosition() {
    return _arrayStart->getStartPosition();
}

std::shared_ptr<Position> ASTArrayTypeNode::getEndPosition() {
    return _arrayEnd->getEndPosition();
}

ASTNodeType ASTArrayTypeNode::getNodeType() {
    return AST_ARRAY_TYPE_NODE;
}

std::string ASTArrayTypeNode::toString() {
    return "ARRAY_TYPE";
}

bool ASTArrayTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }

    auto otherNode = std::dynamic_pointer_cast<ASTArrayTypeNode>(other);
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