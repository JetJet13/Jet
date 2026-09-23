//
// Created by Johny Georges on 2026-02-20.
//

#ifndef JETLANG_IR_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-class-property-shared-value-assignment-statement-node.h"

class IRClassPropertySharedValueAssignmentStatementNode : public IRStatementNode {
private:
    std::shared_ptr<ASTClassPropertySharedValueAssignmentStatementNode> _node;
    std::shared_ptr<IRExpressionNode> _irExpression;
    std::string _propertyName;
    uint64_t _propertyIndex;
public:
    IRClassPropertySharedValueAssignmentStatementNode(std::shared_ptr<ASTClassPropertySharedValueAssignmentStatementNode> node, std::shared_ptr<IRExpressionNode> irExpression, std::string propertyName, uint64_t propertyIndex);
    std::shared_ptr<IRExpressionNode> getExpression();
    uint64_t getPropertyIndex();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
