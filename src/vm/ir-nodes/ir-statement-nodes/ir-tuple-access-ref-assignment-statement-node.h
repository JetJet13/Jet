//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_IR_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../ir-expression-nodes/ir-tuple-access-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-tuple-access-ref-assignment-statement-node.h"

class IRTupleAccessRefAssignmentStatementNode : public IRStatementNode {
private:
    std::shared_ptr<ASTTupleAccessRefAssignmentStatementNode> _node;
    std::shared_ptr<IRTupleAccessExpressionNode> _irTupleAccessExpression;
    std::shared_ptr<IRExpressionNode> _irExpression;
public:
    IRTupleAccessRefAssignmentStatementNode(std::shared_ptr<ASTTupleAccessRefAssignmentStatementNode> node, std::shared_ptr<IRTupleAccessExpressionNode> irTupleAccessExpression, std::shared_ptr<IRExpressionNode> irExpression);
    std::shared_ptr<IRTupleAccessExpressionNode> getIRTupleAccessExpression();
    std::shared_ptr<IRExpressionNode> getIRExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H
