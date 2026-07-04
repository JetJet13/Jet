//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-try-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTryStatementNode::ASTTryStatementNode(std::shared_ptr<ASTTryBlockNode> tryBlock, std::shared_ptr<ASTCatchBlockNode> catchBlock) {
    _tryBlock = tryBlock;
    _catchBlock = catchBlock;
    _finallyBlock = {};
    _children.push_back(_tryBlock);
    _children.push_back(_catchBlock);
}

ASTTryStatementNode::ASTTryStatementNode(std::shared_ptr<ASTTryBlockNode> tryBlock, std::shared_ptr<ASTCatchBlockNode> catchBlock, std::shared_ptr<ASTFinallyBlockNode> finallyBlock) {
    _tryBlock = tryBlock;
    _catchBlock = catchBlock;
    _finallyBlock = finallyBlock;
    _children.push_back(_tryBlock);
    _children.push_back(_catchBlock);
    _children.push_back(_finallyBlock.value());

}

std::shared_ptr<ASTTryBlockNode> ASTTryStatementNode::getTryBlock() {
    return _tryBlock;
}

std::shared_ptr<ASTCatchBlockNode> ASTTryStatementNode::getCatchBlock() {
    return _catchBlock;
}

std::optional<std::shared_ptr<ASTFinallyBlockNode>> ASTTryStatementNode::getFinallyBlock() {
    return _finallyBlock;
}

Position* ASTTryStatementNode::getStartPosition() {
    return _tryBlock->getStartPosition();
}

Position* ASTTryStatementNode::getEndPosition() {
    if (_finallyBlock) {
        return _finallyBlock.value()->getEndPosition();
    }
    return _catchBlock->getEndPosition();
}

ASTNodeType ASTTryStatementNode::getNodeType() {
    return AST_TRY_STATEMENT_NODE;
}

std::string ASTTryStatementNode::toString() {
    return "TRY_STATEMENT";
}

bool ASTTryStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTryStatementNode>(other);
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

std::string ASTTryStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tryBlock)
    ->add(_catchBlock);

    if (_finallyBlock) {
        sourceCodeBuilder.add(_finallyBlock.value());
    }

    return sourceCodeBuilder.build();
}