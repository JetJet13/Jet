//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_IR_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-array-access-shared-value-assignment-statement-node.h"
#include "../ir-expression-nodes/ir-array-access-expression-node.h"

class IRArrayAccessSharedValueAssignmentStatementNode : public IRStatementNode {
private:
    std::shared_ptr<ASTArrayAccessSharedValueAssignmentStatementNode> _node;
    std::shared_ptr<IRArrayAccessExpressionNode> _irArrayAccessExpression;
    std::shared_ptr<IRExpressionNode> _irExpression;
public:
    IRArrayAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTArrayAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRArrayAccessExpressionNode> irArrayAccessExpression, std::shared_ptr<IRExpressionNode> irExpression);
    std::shared_ptr<IRArrayAccessExpressionNode> getIRArrayAccessExpression();
    std::shared_ptr<IRExpressionNode> getIRExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
