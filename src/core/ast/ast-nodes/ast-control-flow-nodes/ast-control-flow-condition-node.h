//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_CONTROL_FLOW_CONDITION_NODE_H
#define JETLANG_AST_CONTROL_FLOW_CONDITION_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-expression-nodes/ast-expression-node.h"

class ASTControlFlowConditionNode : public ASTNode {
private:
    ASTExpressionNode* _condition;
public:
    ASTControlFlowConditionNode(ASTExpressionNode* condition);
    ASTExpressionNode* getCondition();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CONTROL_FLOW_CONDITION_NODE_H
