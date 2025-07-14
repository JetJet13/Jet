//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-try-block-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTTryBlockNode::ASTTryBlockNode(ASTTryNode* tryKeyword, ASTControlFlowBlockNode* block) {
    _tryKeyword = tryKeyword;
    _block = block;
    _children.push_back(_tryKeyword);
    _children.push_back(_block);
}

ASTControlFlowBlockNode* ASTTryBlockNode::getBlock() {
    return _block;
}

Position* ASTTryBlockNode::getStartPosition() {
    return _tryKeyword->getStartPosition();
}

Position* ASTTryBlockNode::getEndPosition() {
    return _block->getEndPosition();
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

std::string ASTTryBlockNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tryKeyword)
    ->add(_block);
    return sourceCodeBuilder.build();
}