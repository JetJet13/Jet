//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-else-block-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTElseBlockNode::ASTElseBlockNode(std::shared_ptr<ASTElseNode> elseKeyword, std::shared_ptr<ASTControlFlowBlockNode> block) {
    _elseKeyword = elseKeyword;
    _block = block;
    _children.push_back(_block);
}

std::shared_ptr<ASTControlFlowBlockNode> ASTElseBlockNode::getBlock() {
    return _block;
}

std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* ASTElseBlockNode::getReturnStatements() {
    return _block->getReturnStatements();
}

std::shared_ptr<Position> ASTElseBlockNode::getStartPosition() {
    return _elseKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTElseBlockNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTElseBlockNode::getNodeType() {
    return AST_ELSE_BLOCK_NODE;
}

std::string ASTElseBlockNode::toString() {
    return "ELSE_BLOCK";
}

bool ASTElseBlockNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTElseBlockNode>(other);

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