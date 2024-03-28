//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-control-flow-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTControlFlowStatementNode::ASTControlFlowStatementNode(ASTIfBlockNode* ifBlock) {
    _ifBlock = ifBlock;
    _elseIfBlocks = std::vector<ASTElseIfBlockNode*>();
    _elseBlock = {};
}

ASTControlFlowStatementNode::ASTControlFlowStatementNode(ASTIfBlockNode* ifBlock, std::vector<ASTElseIfBlockNode*> elseIfBlocks, std::optional<ASTElseBlockNode*> elseBlock) {
    _ifBlock = ifBlock;
    _elseBlock = elseBlock;
    _elseIfBlocks = std::vector<ASTElseIfBlockNode*>();
    for (auto elseIfBlock: elseIfBlocks) {
        _elseIfBlocks.push_back(elseIfBlock);
    }
}

ASTControlFlowStatementNode* ASTControlFlowStatementNode::addElseIfBlock(ASTElseIfBlockNode* elseIfBlock) {
    _elseIfBlocks.push_back(elseIfBlock);
    return this;
}

ASTIfBlockNode* ASTControlFlowStatementNode::getIfBlock() {
    return _ifBlock;
}

std::vector<ASTElseIfBlockNode*>* ASTControlFlowStatementNode::getElseIfBlocks() {
    return &_elseIfBlocks;
}

std::optional<ASTElseBlockNode*> ASTControlFlowStatementNode::getElseBlock() {
    return _elseBlock;
}

ASTNodeType ASTControlFlowStatementNode::getNodeType() {
    return AST_CONTROL_FLOW_STATEMENT_NODE;
}

std::string ASTControlFlowStatementNode::toString() {
    return "CONTROL_FLOW_STATEMENT";
}

bool ASTControlFlowStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTControlFlowStatementNode*)other;
    if (!this->getIfBlock()->isSameAs(otherNode->getIfBlock())) {
        return false;
    }

    if (!_elseBlock.has_value() && otherNode->getElseBlock().has_value() ||
        _elseBlock.has_value() && !otherNode->getElseBlock().has_value()) {
        return false;
    }

    if (_elseBlock.has_value() && otherNode->getElseBlock().has_value() &&
        !_elseBlock.value()->isSameAs(otherNode->getElseBlock().value())) {
        return false;
    }

    for (int i = 0; i < _elseIfBlocks.size(); ++i) {
        if (!_elseIfBlocks[i]->isSameAs(otherNode->getElseIfBlocks()->at(i))) {
            return false;
        }
    }
    return true;
}


void ASTControlFlowStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _ifBlock->print();
    for (auto elseIfBlock : _elseIfBlocks) {
        elseIfBlock->print();
    }
    if (_elseBlock) {
        _elseBlock.value()->print();
    }
    Logger::log("----------");
}