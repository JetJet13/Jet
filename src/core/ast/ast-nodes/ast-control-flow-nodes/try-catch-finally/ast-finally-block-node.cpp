//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-finally-block-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTFinallyBlockNode::ASTFinallyBlockNode(ASTFinallyNode* finallyKeyword, ASTControlFlowBlockNode* block) {
    _finallyKeyword = finallyKeyword;
    _block = block;
    _children.push_back(_finallyKeyword);
    _children.push_back(_block);
}

ASTControlFlowBlockNode* ASTFinallyBlockNode::getBlock() {
    return _block;
}

ASTNodeType ASTFinallyBlockNode::getNodeType() {
    return AST_FINALLY_BLOCK_NODE;
}

std::string ASTFinallyBlockNode::toString() {
    return "FINALLY_BLOCK";
}

bool ASTFinallyBlockNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFinallyBlockNode*)other;

    return this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTFinallyBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _block->print();
    Logger::log("----------");
}

std::string ASTFinallyBlockNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_finallyKeyword)
    ->addWithWhitespace(_block);
    return sourceCodeBuilder.build();
}