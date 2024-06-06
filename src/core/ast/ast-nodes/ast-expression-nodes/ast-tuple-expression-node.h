//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_TUPLE_EXPRESSION_NODE_H
#define JETLANG_AST_TUPLE_EXPRESSION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "ast-expression-node.h"
#include "../ast-struct-nodes/ast-struct-key-value-node.h"
#include "../ast-tuple-nodes/ast-tuple-list-node.h"

class ASTTupleExpressionNode : public ASTExpressionNode {
private:
    ASTTupleListNode* _tupleList;
public:
    ASTTupleExpressionNode(ASTTupleListNode* tupleList);
    ASTTupleListNode* getTupleList();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_EXPRESSION_NODE_H
