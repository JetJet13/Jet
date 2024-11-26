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
    ASTExpressionStatementNode* _node;
    IRExpressionNode* _irExpression;
public:
    IRExpressionStatementNode(ASTExpressionStatementNode* node, IRExpressionNode* irExpression);
    IRExpressionNode* getExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_EXPRESSION_STATEMENT_NODE_H
