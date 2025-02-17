//
// Created by Johny Georges on 2025-02-17.
//

#ifndef JETLANG_IR_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-array-access-assignment-statement-node.h"
#include "../ir-expression-nodes/ir-array-access-expression-node.h"


class IRArrayAccessAssignmentStatementNode : public IRStatementNode {
private:
    ASTArrayAccessAssignmentStatementNode* _node;
    IRArrayAccessExpressionNode* _irArrayAccessExpression;
    IRExpressionNode* _irExpression;
public:
    IRArrayAccessAssignmentStatementNode(ASTArrayAccessAssignmentStatementNode* node, IRArrayAccessExpressionNode* irArrayAccessExpression, IRExpressionNode* irExpression);
    IRArrayAccessExpressionNode* getIRArrayAccessExpression();
    IRExpressionNode* getIRExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
