//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleNameNode::ASTModuleNameNode(std::shared_ptr<ASTIdentifierNode> identifier) {
    _identifier = identifier;
    _children.push_back(_identifier);
}

std::shared_ptr<ASTIdentifierNode> ASTModuleNameNode::getIdentifier() {
    return _identifier;
}

Position* ASTModuleNameNode::getStartPosition() {
    return _identifier->getStartPosition();
}

Position* ASTModuleNameNode::getEndPosition() {
    return _identifier->getEndPosition();
}

ASTNodeType ASTModuleNameNode::getNodeType() {
    return AST_MODULE_NAME_NODE;
}

std::string ASTModuleNameNode::toString() {
    return "MODULE_NAME";
}

bool ASTModuleNameNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleNameNode>(other);
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTModuleNameNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}

std::string ASTModuleNameNode::toSourceCode() {
    return _identifier->toSourceCode();
}