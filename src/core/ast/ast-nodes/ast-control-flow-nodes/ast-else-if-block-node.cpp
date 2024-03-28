//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-else-if-block-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTElseIfBlockNode::ASTElseIfBlockNode(ASTControlFlowConditionNode* condition, ASTControlFlowBlockNode* block) {
    _condition = condition;
    _block = block;
}

ASTControlFlowBlockNode* ASTElseIfBlockNode::getBlock() {
    return _block;
}

ASTControlFlowConditionNode* ASTElseIfBlockNode::getCondition() {
    return _condition;
}

ASTNodeType ASTElseIfBlockNode::getNodeType() {
    return AST_ELSE_IF_BLOCK_NODE;
}

std::string ASTElseIfBlockNode::toString() {
    return "ELSE_IF_BLOCK";
}

bool ASTElseIfBlockNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTElseIfBlockNode*)other;

    return  this->getCondition()->isSameAs(otherNode->getCondition()) &&
            this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTElseIfBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _condition->print();
    _block->print();
    Logger::log("----------");
}