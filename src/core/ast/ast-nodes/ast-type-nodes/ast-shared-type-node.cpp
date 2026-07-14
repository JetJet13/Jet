//
// Created by Johny Georges on 2026-07-11.
//

#include "ast-shared-type-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTSharedTypeNode::ASTSharedTypeNode(std::shared_ptr<ASTSharedNode> sharedNode, std::shared_ptr<ASTTypeParameterListNode> typeParameterList) {
    _shared = sharedNode;
    _typeParameterList = typeParameterList;
    _children.push_back(_shared);
    _children.push_back(_typeParameterList);
}

std::shared_ptr<ASTTypeNode> ASTSharedTypeNode::getSharedType() {
    return _typeParameterList->getParameters()[0];
}

std::shared_ptr<Position> ASTSharedTypeNode::getStartPosition() {
    return _shared->getStartPosition();
}

std::shared_ptr<Position> ASTSharedTypeNode::getEndPosition() {
    return _typeParameterList->getEndPosition();
}

ASTNodeType ASTSharedTypeNode::getNodeType() {
    return AST_SHARED_TYPE_NODE;
}

std::string ASTSharedTypeNode::toString() {
    return "SHARED_TYPE";
}

bool ASTSharedTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }

    auto otherNode = std::dynamic_pointer_cast<ASTSharedTypeNode>(other);
    return this->getSharedType()->isSameAs(otherNode->getSharedType());
}

void ASTSharedTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _typeParameterList->print();
    Logger::log("----------");
}

std::string ASTSharedTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_shared)->add(_typeParameterList);
    return sourceCodeBuilder.build();
}