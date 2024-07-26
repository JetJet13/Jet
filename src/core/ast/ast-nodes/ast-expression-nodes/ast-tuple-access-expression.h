//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_TUPLE_ACCESS_EXPRESSION_H
#define JETLANG_AST_TUPLE_ACCESS_EXPRESSION_H

#include "ast-aggregate-expression-node.h"
#include "../ast-tuple-nodes/ast-tuple-access-node.h"
#include "../ast-object-nodes/ast-object-access-source-node.h"
#include "../ast-period-node.h"

class ASTTupleAccessExpressionNode : public ASTAggregateExpressionNode {
private:
    ASTObjectAccessSourceNode* _source;
    ASTPeriodNode* _period;
    ASTTupleAccessNode* _index;
public:
    ASTTupleAccessExpressionNode(ASTObjectAccessSourceNode* source, ASTPeriodNode* period, ASTTupleAccessNode* index);
    ASTObjectAccessSourceNode* getSource();
    ASTTupleAccessNode* getIndex();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_ACCESS_EXPRESSION_H
