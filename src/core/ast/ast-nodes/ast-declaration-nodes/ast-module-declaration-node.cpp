//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleDeclarationNode::ASTModuleDeclarationNode(ASTModuleNameNode* name, ASTModuleListNode* items) {
    _name = name;
    _items = items;
}

ASTModuleListNode* ASTModuleDeclarationNode::getValues() {
    return _values;
}

ASTModuleNameNode* ASTModuleDeclarationNode::getName() {
    return _name;
}

ASTNodeType ASTModuleDeclarationNode::getNodeType() {
    return AST_MODULE_DECLARATION_NODE;
}

std::string ASTModuleDeclarationNode::toString() {
    return "MODULE_DECLARATION";
}

bool ASTModuleDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTModuleDeclarationNode*)other;

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getItems()->isSameAs(otherNode->getItems());
}

void ASTModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _items->print();
    Logger::log("----------");
}