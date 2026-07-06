//
// Created by Johny Georges on 2024-11-25.
//

#ifndef JETLANG_IR_EXPRESSION_STATEMENT_NODE_H
#define JETLANG_IR_EXPRESSION_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-expression-statement-node.h"


class IRExpressionStatementNode : public IRStatementNode {
private:
    std::shared_ptr<ASTExpressionStatementNode> _node;
    std::shared_ptr<IRExpressionNode> _irExpression;
public:
    IRExpressionStatementNode(std::shared_ptr<ASTExpressionStatementNode> node, std::shared_ptr<IRExpressionNode> irExpression);
    std::shared_ptr<IRExpressionNode> getExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_EXPRESSION_STATEMENT_NODE_H
