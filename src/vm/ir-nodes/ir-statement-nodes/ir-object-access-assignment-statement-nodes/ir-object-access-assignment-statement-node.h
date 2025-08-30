//
// Created by Johny Georges on 2025-08-30.
//

#ifndef JETLANG_IR_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE_H

#include "../../ir-expression-nodes/ir-expression-node.h"
#include "../ir-statement-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-object-access-assignment-statement-node.h"
#include "../../ir-expression-nodes/ir-object-access-expression-node.h"

class IRObjectAccessAssignmentStatementNode : public IRStatementNode {
private:
    ASTObjectAccessAssignmentStatementNode* _node;
    IRObjectAccessExpressionNode* _irObjectAccessExpression;
    IRExpressionNode* _irExpression;
public:
    IRObjectAccessAssignmentStatementNode(ASTObjectAccessAssignmentStatementNode* node, IRObjectAccessExpressionNode* irObjectAccessExpression, IRExpressionNode* irExpression);
    IRObjectAccessExpressionNode* getIRObjectAccessExpression();
    IRExpressionNode* getIRExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
