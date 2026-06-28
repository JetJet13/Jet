//
// Created by Johny Georges on 2026-03-16.
//

#ifndef JETLANG_IR_CLASS_STATIC_PROPERTY_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_CLASS_STATIC_PROPERTY_ASSIGNMENT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-object-access-assignment-statement-node.h"
#include "../ir-expression-nodes/ir-object-access-expression-node.h"
#include "../ir-expression-nodes/ir-class-static-property-access-expression-node.h"

class IRClassStaticPropertyAssignmentStatementNode : public IRStatementNode {
private:
    ASTObjectAccessAssignmentStatementNode* _node;
    IRClassStaticPropertyAccessExpressionNode* _irClassStaticPropertyAccessExpressionNode;
    IRExpressionNode* _irExpression;
public:
    IRClassStaticPropertyAssignmentStatementNode(ASTObjectAccessAssignmentStatementNode* node, IRClassStaticPropertyAccessExpressionNode* irClassStaticPropertyAccessExpressionNode, IRExpressionNode* irExpression);
    IRClassStaticPropertyAccessExpressionNode* getIRClassStaticPropertyAccessExpressionNode();
    IRExpressionNode* getIRExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CLASS_STATIC_PROPERTY_ASSIGNMENT_STATEMENT_NODE_H
