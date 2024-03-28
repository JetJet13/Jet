//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-control-flow-block-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTControlFlowBlockNode::ASTControlFlowBlockNode(std::vector<ASTNode*> contents) {
    _contents = std::vector<ASTNode*>();
    for (auto content: contents) {
        _contents.push_back(content);
    }
}

std::vector<ASTNode*> ASTControlFlowBlockNode::getContents() {
    return _contents;
}

ASTNodeType ASTControlFlowBlockNode::getNodeType() {
    return AST_CONTROL_FLOW_BLOCK_NODE;
}

std::string ASTControlFlowBlockNode::toString() {
    return "CONTROL_FLOW_BLOCK";
}

bool ASTControlFlowBlockNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTControlFlowBlockNode*)other;
    for (int i = 0; i < _contents.size(); ++i) {
        if (!_contents[i]->isSameAs(otherNode->getContents()[i])) {
            return false;
        }
    }
    return true;
}

void ASTControlFlowBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto content : _contents) {
        content->print();
    }
    Logger::log("----------");
}