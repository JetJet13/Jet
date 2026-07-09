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
    std::shared_ptr<ASTObjectAccessSourceNode> _source;
    std::shared_ptr<ASTPeriodNode> _period;
    std::shared_ptr<ASTTupleAccessNode> _index;
public:
    ASTTupleAccessExpressionNode(std::shared_ptr<ASTObjectAccessSourceNode> source, std::shared_ptr<ASTPeriodNode> period, std::shared_ptr<ASTTupleAccessNode> index);
    std::shared_ptr<ASTObjectAccessSourceNode> getSource();
    std::shared_ptr<ASTTupleAccessNode> getIndex();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_ACCESS_EXPRESSION_H
