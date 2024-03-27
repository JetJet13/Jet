//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_TUPLE_LIST_NODE_H
#define JETLANG_AST_TUPLE_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-tuple-item-node.h"

class ASTTupleListNode : public ASTNode {
private:
    std::vector<ASTTupleItemNode*> _items;
public:
    ASTTupleListNode();
    ASTTupleListNode(std::vector<ASTTupleItemNode*> items);
    std::vector<ASTTupleItemNode*> getItems();
    unsigned long numItems();
    ASTTupleListNode* addItem(ASTTupleItemNode* item);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_TUPLE_LIST_NODE_H
