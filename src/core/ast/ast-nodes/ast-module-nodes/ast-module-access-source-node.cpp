//
// Created by Johny Georges on 2024-11-05.
//

#include "ast-module-access-source-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleAccessSourceNode::ASTModuleAccessSourceNode(std::shared_ptr<ASTIdentifierExpressionNode> source) {
    _source = source;
    _children.push_back(_source);
}

std::shared_ptr<ASTIdentifierExpressionNode> ASTModuleAccessSourceNode::getSource() {
    return _source;
}

std::shared_ptr<Position> ASTModuleAccessSourceNode::getStartPosition() {
    return _source->getStartPosition();
}

std::shared_ptr<Position> ASTModuleAccessSourceNode::getEndPosition() {
    return _source->getEndPosition();
}

ASTNodeType ASTModuleAccessSourceNode::getNodeType() {
    return AST_MODULE_ACCESS_SOURCE_NODE;
}

std::string ASTModuleAccessSourceNode::toString() {
    return "MODULE_ACCESS_SOURCE";
}

bool ASTModuleAccessSourceNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleAccessSourceNode>(other);
    return this->getSource()->isSameAs(otherNode->getSource());
}

void ASTModuleAccessSourceNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    Logger::log("----------");
}

std::string ASTModuleAccessSourceNode::toSourceCode() {
    return _source->toSourceCode();
}