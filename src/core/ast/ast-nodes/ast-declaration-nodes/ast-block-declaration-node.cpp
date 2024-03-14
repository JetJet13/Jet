//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-block-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTBlockDeclarationNode::ASTBlockDeclarationNode() {
    _contents = std::vector<ASTNode*>();
}

ASTBlockDeclarationNode::ASTBlockDeclarationNode(std::vector<ASTNode*> contents) {
    _contents = std::vector<ASTNode*>();
    for (auto content: contents) {
        _contents.push_back(content);
    }
}

ASTBlockDeclarationNode* ASTBlockDeclarationNode::addContent(ASTNode* content) {
    _contents.push_back(content);
    return this;
}

std::vector<ASTNode*> ASTBlockDeclarationNode::getContents() {
    return _contents;
}

unsigned long ASTBlockDeclarationNode::size() {
    return _contents.size();
}

ASTNodeType ASTBlockDeclarationNode::getNodeType() {
    return AST_BLOCK_DECLARATION_NODE;
}

std::string ASTBlockDeclarationNode::toString() {
    return "BLOCK_DECLARATION";
}

bool ASTBlockDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTBlockDeclarationNode*)other;
    auto otherNodeElements = otherNode->getContents();
    if (this->size() != otherNode->size()) {
        return false;
    }
    for (int i = 0; i < this->size(); i++) {
        if (!_contents[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTBlockDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto content : _contents) {
        content->print();
    }
    Logger::log("----------");
}