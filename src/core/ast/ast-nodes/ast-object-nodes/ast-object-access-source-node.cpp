//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-object-access-source-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTObjectAccessSourceNode::ASTObjectAccessSourceNode(std::shared_ptr<ASTExpressionNode> source) {
    _source = source;
    _children.push_back(_source);
}

std::shared_ptr<ASTExpressionNode> ASTObjectAccessSourceNode::getSource() {
    return _source;
}

Position* ASTObjectAccessSourceNode::getStartPosition() {
    return _source->getStartPosition();
}

Position* ASTObjectAccessSourceNode::getEndPosition() {
    return _source->getEndPosition();
}

ASTNodeType ASTObjectAccessSourceNode::getNodeType() {
    return AST_OBJECT_ACCESS_SOURCE_NODE;
}

std::string ASTObjectAccessSourceNode::toString() {
    return "OBJECT_ACCESS_SOURCE";
}

bool ASTObjectAccessSourceNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTObjectAccessSourceNode>(other);
    return this->getSource()->isSameAs(otherNode->getSource());
}

void ASTObjectAccessSourceNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    Logger::log("----------");
}

std::string ASTObjectAccessSourceNode::toSourceCode() {
    return _source->toSourceCode();
}