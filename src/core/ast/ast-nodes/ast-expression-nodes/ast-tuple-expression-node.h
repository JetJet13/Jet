//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_TUPLE_EXPRESSION_NODE_H
#define JETLANG_AST_TUPLE_EXPRESSION_NODE_H

#include <vector>
#include "ast-aggregate-expression-node.h"
#include "../ast-node.h"
#include "../ast-struct-nodes/ast-struct-key-value-node.h"
#include "../ast-tuple-nodes/ast-tuple-list-node.h"
#include "../ast-tuple-nodes/ast-tuple-node.h"
#include "../../../type-signature/tuple-type-signature/tuple-type-signature.h"

class ASTTupleExpressionNode : public ASTAggregateExpressionNode {
private:
    ASTTupleNode* _tupleKeyword;
    ASTTupleListNode* _tupleList;
    TupleTypeSignature* _typeSignature = new TupleTypeSignature();
public:
    ASTTupleExpressionNode(ASTTupleNode* tupleKeyword, ASTTupleListNode* tupleList);
    ASTTupleListNode* getTupleList();
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
