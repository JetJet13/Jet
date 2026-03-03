//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_TUPLE_EXPRESSION_NODE_H
#define JETLANG_AST_TUPLE_EXPRESSION_NODE_H

#include <vector>
#include "ast-aggregate-expression-node.h"
#include "../ast-node.h"
#include "../ast-tuple-nodes/ast-tuple-list-start-node.h"
#include "../ast-tuple-nodes/ast-tuple-item-node.h"
#include "../ast-tuple-nodes/ast-tuple-list-end-node.h"
#include "../ast-comma-node.h"
#include "../../../type-signature/tuple-type-signature/tuple-type-signature.h"

class ASTTupleExpressionNode : public ASTAggregateExpressionNode {
private:
    ASTTupleListStartNode* _tupleListStart;
    ASTTupleListEndNode* _tupleListEnd;
    std::vector<ASTCommaNode*> _commas;
    std::vector<ASTTupleItemNode*> _items;
    TupleTypeSignature* _typeSignature = new TupleTypeSignature();
public:
    ASTTupleExpressionNode(ASTTupleListStartNode* tupleListStart, ASTTupleListEndNode* tupleListEnd);
    ASTTupleExpressionNode(ASTTupleListStartNode* tupleListStart, std::vector<ASTTupleItemNode*> items, std::vector<ASTCommaNode*> commas, ASTTupleListEndNode* tupleListEnd);
    std::vector<ASTTupleItemNode*>* getItems();
    unsigned long numItems();
    ASTTupleExpressionNode* addItem(ASTTupleItemNode* item);
    ASTTupleExpressionNode* addComma(ASTCommaNode* comma);
    TupleTypeSignature* getTypeSignature() override;
    void setTypeSignature(TupleTypeSignature* tupleTypeSignature);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_EXPRESSION_NODE_H
