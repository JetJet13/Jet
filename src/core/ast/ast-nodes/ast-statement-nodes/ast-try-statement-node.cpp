//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-try-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTryStatementNode::ASTTryStatementNode(ASTTryBlockNode* tryBlock, ASTCatchBlockNode* catchBlock) {
    _tryBlock = tryBlock;
    _catchBlock = catchBlock;
    _finallyBlock = {};
    _children.push_back(_tryBlock);
    _children.push_back(_catchBlock);
}

ASTTryStatementNode::ASTTryStatementNode(ASTTryBlockNode* tryBlock, ASTCatchBlockNode* catchBlock, ASTFinallyBlockNode* finallyBlock) {
    _tryBlock = tryBlock;
    _catchBlock = catchBlock;
    _finallyBlock = finallyBlock;
    _children.push_back(_tryBlock);
    _children.push_back(_catchBlock);
    _children.push_back(_finallyBlock.value());

}

ASTTryBlockNode* ASTTryStatementNode::getTryBlock() {
    return _tryBlock;
}

ASTCatchBlockNode* ASTTryStatementNode::getCatchBlock() {
    return _catchBlock;
}

std::optional<ASTFinallyBlockNode*> ASTTryStatementNode::getFinallyBlock() {
    return _finallyBlock;
}

ASTNodeType ASTTryStatementNode::getNodeType() {
    return AST_TRY_STATEMENT_NODE;
}

std::string ASTTryStatementNode::toString() {
    return "TRY_STATEMENT";
}

bool ASTTryStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTTryStatementNode*)other;
    if (!this->getTryBlock()->isSameAs(otherNode->getTryBlock())) {
        return false;
    }

    if (!_finallyBlock.has_value() && otherNode->getFinallyBlock().has_value() ||
        _finallyBlock.has_value() && !otherNode->getFinallyBlock().has_value()) {
        return false;
    }

    if (_finallyBlock.has_value() && otherNode->getFinallyBlock().has_value() &&
        !_finallyBlock.value()->isSameAs(otherNode->getFinallyBlock().value())) {
        return false;
    }

    return _catchBlock->isSameAs(otherNode->getCatchBlock());
}


void ASTTryStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _tryBlock->print();
    _catchBlock->print();
    if (_finallyBlock) {
        _finallyBlock.value()->print();
    }
    Logger::log("----------");
}