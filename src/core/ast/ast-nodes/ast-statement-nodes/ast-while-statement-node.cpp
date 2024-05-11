//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-while-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTWhileStatementNode::ASTWhileStatementNode(ASTControlFlowConditionNode* condition, ASTControlFlowBlockNode* block) {
    _condition = condition;
    _block = block;
    _children.push_back(_condition);
    _children.push_back(_block);
}

ASTControlFlowBlockNode* ASTWhileStatementNode::getBlock() {
    return _block;
}

ASTControlFlowConditionNode* ASTWhileStatementNode::getCondition() {
    return _condition;
}

ASTNodeType ASTWhileStatementNode::getNodeType() {
    return AST_WHILE_STATEMENT_NODE;
}

std::string ASTWhileStatementNode::toString() {
    return "WHILE_STATEMENT";
}

bool ASTWhileStatementNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTWhileStatementNode*)other;

    return  this->getCondition()->isSameAs(otherNode->getCondition()) &&
            this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTWhileStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _condition->print();
    _block->print();
    Logger::log("----------");
}