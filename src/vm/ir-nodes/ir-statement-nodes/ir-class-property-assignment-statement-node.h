//
// Created by Johny Georges on 2025-01-02.
//

#ifndef JETLANG_IR_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-class-property-assignment-statement-node.h"

class IRClassPropertyAssignmentStatementNode : public IRStatementNode {
private:
    std::shared_ptr<ASTClassPropertyAssignmentStatementNode> _node;
    std::shared_ptr<IRExpressionNode> _irExpression;
    std::string _propertyName;
    unsigned long _propertyIndex;
public:
    IRClassPropertyAssignmentStatementNode(std::shared_ptr<ASTClassPropertyAssignmentStatementNode> node, std::shared_ptr<IRExpressionNode> irExpression, std::string propertyName, unsigned long propertyIndex);
    std::shared_ptr<IRExpressionNode> getExpression();
    unsigned long getPropertyIndex();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE_H
