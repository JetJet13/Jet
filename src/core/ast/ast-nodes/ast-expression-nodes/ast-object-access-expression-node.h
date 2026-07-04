//
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_AST_OBJECT_ACCESS_EXPRESSION_NODE_H
#define JETLANG_AST_OBJECT_ACCESS_EXPRESSION_NODE_H

#include <string>
#include "../ast-object-nodes/ast-object-access-source-node.h"
#include "../ast-object-nodes/ast-object-access-target-node.h"
#include "../ast-period-node.h"
#include "ast-aggregate-expression-node.h"

class ASTObjectAccessExpressionNode : public ASTAggregateExpressionNode {
private:
    std::shared_ptr<ASTObjectAccessSourceNode> _source;
    std::shared_ptr<ASTPeriodNode> _period;
    std::shared_ptr<ASTObjectAccessTargetNode> _target;
public:
    ASTObjectAccessExpressionNode(std::shared_ptr<ASTObjectAccessSourceNode> source, std::shared_ptr<ASTPeriodNode> period, std::shared_ptr<ASTObjectAccessTargetNode> property);
    std::shared_ptr<ASTObjectAccessSourceNode> getSource();
    std::shared_ptr<ASTObjectAccessTargetNode> getTarget();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_EXPRESSION_NODE_H
