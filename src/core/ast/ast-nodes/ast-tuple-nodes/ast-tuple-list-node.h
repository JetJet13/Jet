//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_TUPLE_LIST_NODE_H
#define JETLANG_AST_TUPLE_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-tuple-item-node.h"
#include "ast-tuple-list-start-node.h"
#include "ast-tuple-list-end-node.h"

class ASTTupleListNode : public ASTNode {
private:
    ASTTupleListStartNode* _tupleListStart;
    ASTTupleListEndNode* _tupleListEnd;
    std::vector<ASTTupleItemNode*> _items;
public:
    ASTTupleListNode(ASTTupleListStartNode* tupleListStart, ASTTupleListEndNode* tupleListEnd);
    ASTTupleListNode(ASTTupleListStartNode* tupleListStart, std::vector<ASTTupleItemNode*> items, ASTTupleListEndNode* tupleListEnd);
    std::vector<ASTTupleItemNode*> getItems();
    unsigned long numItems();
    ASTTupleListNode* addItem(ASTTupleItemNode* item);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_LIST_NODE_H
