//
// Created by Johny Georges on 2026-02-20.
//

#ifndef JETLANG_IR_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-shared-value-assignment-statement-node.h"


class IRSharedValueAssignmentStatementNode : public IRStatementNode {
private:
    std::shared_ptr<ASTSharedValueAssignmentStatementNode> _node;
    std::shared_ptr<IRExpressionNode> _irExpression;
public:
    IRSharedValueAssignmentStatementNode(std::shared_ptr<ASTSharedValueAssignmentStatementNode> node, std::shared_ptr<IRExpressionNode> irExpression);
    std::string getVariableName();
    std::shared_ptr<IRExpressionNode> getIRExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
