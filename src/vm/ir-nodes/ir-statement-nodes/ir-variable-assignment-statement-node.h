//
// Created by Johny Georges on 2025-01-06.
//

#ifndef JETLANG_IR_VARIABLE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_VARIABLE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-variable-assignment-statement-node.h"


class IRVariableAssignmentStatementNode : public IRStatementNode {
private:
    std::shared_ptr<ASTVariableAssignmentStatementNode> _node;
    IRExpressionNode* _irExpression;
public:
    IRVariableAssignmentStatementNode(std::shared_ptr<ASTVariableAssignmentStatementNode> node, IRExpressionNode* irExpression);
    std::string getVariableName();
    IRExpressionNode* getIRExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_VARIABLE_ASSIGNMENT_STATEMENT_NODE_H
