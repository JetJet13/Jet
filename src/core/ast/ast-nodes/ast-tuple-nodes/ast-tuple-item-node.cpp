//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-item-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTupleItemNode::ASTTupleItemNode(ASTExpressionNode* item) {
    _item = item;
    _children.push_back(_item);
}

ASTExpressionNode* ASTTupleItemNode::getItem() {
    return _item;
}

ASTNodeType ASTTupleItemNode::getNodeType() {
    return AST_TUPLE_ITEM_NODE;
}

std::string ASTTupleItemNode::toString() {
    return "TUPLE_ITEM";
}

bool ASTTupleItemNode::isSameAs(ASTNode *other) {
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