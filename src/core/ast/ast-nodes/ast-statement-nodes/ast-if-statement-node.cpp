//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-if-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTIfStatementNode::ASTIfStatementNode(ASTIfBlockNode* ifBlock) {
    _ifBlock = ifBlock;
    _elseIfBlocks = std::vector<ASTElseIfBlockNode*>();
    _elseBlock = {};
    _children.push_back(_ifBlock);
}

ASTIfStatementNode::ASTIfStatementNode(ASTIfBlockNode* ifBlock, std::vector<ASTElseIfBlockNode*> elseIfBlocks, std::optional<ASTElseBlockNode*> elseBlock) {
    _ifBlock = ifBlock;
    _children.push_back(_ifBlock);

    _elseBlock = elseBlock;
    if (_elseBlock) {
        _children.push_back(_elseBlock.value());
    }

    _elseIfBlocks = std::vector<ASTElseIfBlockNode*>();
    for (auto elseIfBlock: elseIfBlocks) {
        _elseIfBlocks.push_back(elseIfBlock);
        _children.push_back(elseIfBlock);
    }
}

ASTIfStatementNode* ASTIfStatementNode::addElseIfBlock(ASTElseIfBlockNode* elseIfBlock) {
    _elseIfBlocks.push_back(elseIfBlock);
    return this;
}

ASTIfBlockNode* ASTIfStatementNode::getIfBlock() {
    return _ifBlock;
}

std::vector<ASTElseIfBlockNode*>* ASTIfStatementNode::getElseIfBlocks() {
    return &_elseIfBlocks;
}

std::optional<ASTElseBlockNode*> ASTIfStatementNode::getElseBlock() {
    return _elseBlock;
}

bool ASTIfStatementNode::onlyHasIfBlock() {
    return _elseIfBlocks.empty() && !_elseBlock;
}

Position* ASTIfStatementNode::getStartPosition() {
    return _ifBlock->getStartPosition();
}

Position* ASTIfStatementNode::getEndPosition() {
    if (_elseBlock) {
        return _elseBlock.value()->getEndPosition();
    }

    if (_elseIfBlocks.empty()) {
        return _ifBlock->getEndPosition();
    }

    return _elseIfBlocks[_elseIfBlocks.size() - 1]->getEndPosition();
}

ASTNodeType ASTIfStatementNode::getNodeType() {
    return AST_IF_STATEMENT_NODE;
}

std::string ASTIfStatementNode::toString() {
    return "IF_STATEMENT";
}

bool ASTIfStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTIfStatementNode*)other;
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

    for (unsigned long i = 0; i < _elseIfBlocks.size(); ++i) {
        if (!_elseIfBlocks[i]->isSameAs(otherNode->getElseIfBlocks()->at(i))) {
            return false;
        }
    }
    return true;
}


void ASTIfStatementNode::print() {
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

std::string ASTIfStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_ifBlock);
    for (auto elseIfBlock : _elseIfBlocks) {
        sourceCodeBuilder.add(elseIfBlock);
    }

    if (_elseBlock) {
        sourceCodeBuilder.add(_elseBlock.value());
    }

    return sourceCodeBuilder.build();
}