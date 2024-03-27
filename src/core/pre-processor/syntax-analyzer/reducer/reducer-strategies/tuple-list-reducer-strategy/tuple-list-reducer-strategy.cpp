//
// Created by Johny Georges on 2024-03-26.
//

#include "tuple-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-tuple-nodes/ast-tuple-list-node.h"

ASTNode* TupleListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto tupleListNode = new ASTTupleListNode();
    for (auto node : nodes) {
        if (node->is(AST_TUPLE_ITEM_NODE)) {
            tupleListNode->addItem((ASTTupleItemNode*)node);
        }
    }
    return tupleListNode;
}