//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-else-block-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTElseBlockNode::ASTElseBlockNode(ASTElseNode* elseKeyword, ASTControlFlowBlockNode* block) {
    _elseKeyword = elseKeyword;
    _block = block;
    _children.push_back(_block);
}

ASTControlFlowBlockNode* ASTElseBlockNode::getBlock() {
    return _block;
}

std::vector<ASTFunctionReturnExpressionNode*>* ASTElseBlockNode::getReturnStatements() {
    return _block->getReturnStatements();
}

Position* ASTElseBlockNode::getStartPosition() {
    return _elseKeyword->getStartPosition();
}

Position* ASTElseBlockNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTElseBlockNode::getNodeType() {
    return AST_ELSE_BLOCK_NODE;
}

std::string ASTElseBlockNode::toString() {
    return "ELSE_BLOCK";
}

bool ASTElseBlockNode::isSameAs(ASTNode* other) {
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

std::string ASTElseBlockNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_elseKeyword)
    ->add(_block);
    return sourceCodeBuilder.build();
}