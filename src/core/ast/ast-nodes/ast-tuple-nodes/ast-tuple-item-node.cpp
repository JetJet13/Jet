//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-item-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTupleItemNode::ASTTupleItemNode(ASTExpressionNode* item) {
    _item = item;
    _children.push_back(_item);
}

ASTNode* ASTTupleItemNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_STRUCT_MODE) {
        return this->getItem();
    }
    return this;
}

ASTExpressionNode* ASTTupleItemNode::getItem() {
    return _item;
}

Position* ASTTupleItemNode::getStartPosition() {
    return _item->getStartPosition();
}

Position* ASTTupleItemNode::getEndPosition() {
    return _item->getEndPosition();
}

ASTNodeType ASTTupleItemNode::getNodeType() {
    return AST_TUPLE_ITEM_NODE;
}

std::string ASTTupleItemNode::toString() {
    return "TUPLE_ITEM";
}

bool ASTTupleItemNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTTupleItemNode*)other;
    return this->getItem()->isSameAs(otherNode->getItem());
}

void ASTTupleItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _item->print();
    Logger::log("----------");
}

std::string ASTTupleItemNode::toSourceCode() {
    return _item->toSourceCode();
}