//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_TUPLE_ITEM_NODE_H
#define JETLANG_AST_TUPLE_ITEM_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-type-node.h"

class ASTTupleItemNode : public ASTNode {
private:
    ASTExpressionNode* _item;
public:
    ASTTupleItemNode(ASTExpressionNode* item);
    ASTExpressionNode* getItem();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_TUPLE_ITEM_NODE_H
