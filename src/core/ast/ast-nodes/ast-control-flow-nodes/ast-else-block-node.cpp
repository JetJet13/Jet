//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-else-block-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTElseBlockNode::ASTElseBlockNode(ASTControlFlowBlockNode* block) {
    _block = block;
}

ASTControlFlowBlockNode* ASTElseBlockNode::getBlock() {
    return _block;
}

ASTNodeType ASTElseBlockNode::getNodeType() {
    return AST_ELSE_BLOCK_NODE;
}

std::string ASTElseBlockNode::toString() {
    return "ELSE_BLOCK";
}

bool ASTElseBlockNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTElseBlockNode*)other;

    return this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTElseBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _block->print();
    Logger::log("----------");
}