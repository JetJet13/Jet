//
// Created by Johny Georges on 2026-02-20.
//

#ifndef JETLANG_IR_REF_VALUE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_REF_VALUE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-ref-value-assignment-statement-node.h"


class IRRefValueAssignmentStatementNode : public IRStatementNode {
private:
    ASTRefValueAssignmentStatementNode* _node;
    IRExpressionNode* _irExpression;
public:
    IRRefValueAssignmentStatementNode(ASTRefValueAssignmentStatementNode* node, IRExpressionNode* irExpression);
    std::string getVariableName();
    IRExpressionNode* getIRExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_REF_VALUE_ASSIGNMENT_STATEMENT_NODE_H
