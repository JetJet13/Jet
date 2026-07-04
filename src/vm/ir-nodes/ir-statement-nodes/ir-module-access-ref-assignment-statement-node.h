//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_IR_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-module-access-ref-assignment-statement-node.h"
#include "../ir-expression-nodes/ir-module-access-expression-node.h"

class IRModuleAccessRefAssignmentStatementNode : public IRStatementNode {
private:
    std::shared_ptr<ASTModuleAccessRefAssignmentStatementNode> _node;
    IRModuleAccessExpressionNode* _irModuleAccessExpression;
    IRExpressionNode* _irExpression;
public:
    IRModuleAccessRefAssignmentStatementNode(std::shared_ptr<ASTModuleAccessRefAssignmentStatementNode> node, IRModuleAccessExpressionNode* irModuleAccessExpression, IRExpressionNode* irExpression);
    IRModuleAccessExpressionNode* getIRModuleAccessExpression();
    IRExpressionNode* getIRExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H
