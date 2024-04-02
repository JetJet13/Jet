//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-try-block-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTTryBlockNode::ASTTryBlockNode(ASTControlFlowBlockNode* block) {
    _block = block;
}

ASTControlFlowBlockNode* ASTTryBlockNode::getBlock() {
    return _block;
}

ASTNodeType ASTTryBlockNode::getNodeType() {
    return AST_TRY_BLOCK_NODE;
}

std::string ASTTryBlockNode::toString() {
    return "TRY_BLOCK";
}

bool ASTTryBlockNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTTryBlockNode*)other;

    return this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTTryBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _block->print();
    Logger::log("----------");
}