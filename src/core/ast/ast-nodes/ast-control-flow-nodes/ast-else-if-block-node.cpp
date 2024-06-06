//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-else-if-block-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTElseIfBlockNode::ASTElseIfBlockNode(ASTElseIfNode* elseIfKeyword, ASTControlFlowConditionNode* condition, ASTControlFlowBlockNode* block) {
    _elseIfKeyword = elseIfKeyword;
    _condition = condition;
    _block = block;
    _children.push_back(_condition);
    _children.push_back(_block);
}

ASTControlFlowBlockNode* ASTElseIfBlockNode::getBlock() {
    return _block;
}

ASTControlFlowConditionNode* ASTElseIfBlockNode::getCondition() {
    return _condition;
}

Position* ASTElseIfBlockNode::getStartPosition() {
    return _elseIfKeyword->getStartPosition();
}

Position* ASTElseIfBlockNode::getEndPosition() {
    return _block->getEndPosition();
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

std::string ASTElseIfBlockNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_elseIfKeyword)
    ->addWithWhitespace(_condition)
    ->addWithWhitespace(_block);
    return sourceCodeBuilder.build();
}