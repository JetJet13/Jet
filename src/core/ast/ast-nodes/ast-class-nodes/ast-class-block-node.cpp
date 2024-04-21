//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-block-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassBlockNode::ASTClassBlockNode(std::vector<ASTNode*> contents) {
    _contents = std::vector<ASTNode*>();
    for (auto content: contents) {
        _contents.push_back(content);
    }
}

std::vector<ASTNode*> ASTClassBlockNode::getContents() {
    return _contents;
}

ASTNodeType ASTClassBlockNode::getNodeType() {
    return AST_CLASS_BLOCK_NODE;
}

std::string ASTClassBlockNode::toString() {
    return "CLASS_BLOCK";
}

bool ASTClassBlockNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTClassBlockNode*)other;
    for (int i = 0; i < _contents.size(); ++i) {
        if (!_contents[i]->isSameAs(otherNode->getContents()[i])) {
            return false;
        }
    }
    return true;
}

void ASTClassBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto content : _contents) {
        content->print();
    }
    Logger::log("----------");
}