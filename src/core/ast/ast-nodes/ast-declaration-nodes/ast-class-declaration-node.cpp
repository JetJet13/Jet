//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassDeclarationNode::ASTClassDeclarationNode(ASTClassNameNode* name, ASTClassBlockNode* block) {
    _name = name;
    _block = block;
    _children.push_back(_name);
    _children.push_back(_block);
}

std::string ASTClassDeclarationNode::getInternalId() {
    return "internal_" + this->getId();
}

std::string ASTClassDeclarationNode::getExternalId() {
    return this->getId();
}

ASTClassBlockNode* ASTClassDeclarationNode::getBlock() {
    return _block;
}

ASTClassNameNode* ASTClassDeclarationNode::getName() {
    return _name;
}

ASTNodeType ASTClassDeclarationNode::getNodeType() {
    return AST_CLASS_DECLARATION_NODE;
}

std::string ASTClassDeclarationNode::toString() {
    return "CLASS_DECLARATION";
}

bool ASTClassDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTClassDeclarationNode*)other;

    return this->getName()->isSameAs(otherNode->getName()) &&
           this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTClassDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _block->print();
    Logger::log("----------");
}