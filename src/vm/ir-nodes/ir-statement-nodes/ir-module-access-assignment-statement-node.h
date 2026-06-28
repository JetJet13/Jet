//
// Created by Johny Georges on 2026-04-02.
//

#ifndef JETLANG_IR_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-module-access-assignment-statement-node.h"
#include "../ir-expression-nodes/ir-module-access-expression-node.h"

class IRModuleAccessAssignmentStatementNode : public IRStatementNode {
private:
    ASTModuleAccessAssignmentStatementNode* _node;
    IRModuleAccessExpressionNode* _irModuleAccessExpression;
    IRExpressionNode* _irExpression;
public:
    IRModuleAccessAssignmentStatementNode(ASTModuleAccessAssignmentStatementNode* node, IRModuleAccessExpressionNode* irModuleAccessExpression, IRExpressionNode* irExpression);
    IRModuleAccessExpressionNode* getIRModuleAccessExpression();
    IRExpressionNode* getIRExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
