//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_IR_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-object-access-ref-assignment-statement-node.h"
#include "../ir-expression-nodes/ir-object-access-expression-node.h"

class IRObjectAccessRefAssignmentStatementNode : public IRStatementNode {
private:
    ASTObjectAccessRefAssignmentStatementNode* _node;
    IRObjectAccessExpressionNode* _irObjectAccessExpression;
    IRExpressionNode* _irExpression;
public:
    IRObjectAccessRefAssignmentStatementNode(ASTObjectAccessRefAssignmentStatementNode* node, IRObjectAccessExpressionNode* irObjectAccessExpression, IRExpressionNode* irExpression);
    IRObjectAccessExpressionNode* getIRObjectAccessExpression();
    IRExpressionNode* getIRExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H
