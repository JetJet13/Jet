//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-if-block-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTIfBlockNode::ASTIfBlockNode(ASTIfNode* ifKeyword, ASTControlFlowConditionNode* condition, ASTControlFlowBlockNode* block) {
    _ifKeyword = ifKeyword;
    _condition = condition;
    _block = block;
    _children.push_back(_condition);
    _children.push_back(_block);
}

ASTControlFlowBlockNode* ASTIfBlockNode::getBlock() {
    return _block;
}

ASTControlFlowConditionNode* ASTIfBlockNode::getCondition() {
    return _condition;
}

ASTNodeType ASTIfBlockNode::getNodeType() {
    return AST_IF_BLOCK_NODE;
}

std::string ASTIfBlockNode::toString() {
    return "IF_BLOCK";
}

bool ASTIfBlockNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTIfBlockNode*)other;

    return  this->getCondition()->isSameAs(otherNode->getCondition()) &&
            this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTIfBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _condition->print();
    _block->print();
    Logger::log("----------");
}

std::string ASTIfBlockNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_ifKeyword)
    ->addWithWhitespace(_condition)
    ->addWithWhitespace(_block);
    return sourceCodeBuilder.build();
}