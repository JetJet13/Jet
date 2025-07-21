//
// Created by Johny Georges on 2025-07-21.
//

#ifndef JETLANG_IR_PRINT_STATEMENT_NODE_H
#define JETLANG_IR_PRINT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-print-statement-node.h"

class IRPrintStatementNode : public IRStatementNode {
private:
    ASTPrintStatementNode* _node;
    std::vector<IRExpressionNode*> _arguments;
public:
    IRPrintStatementNode(ASTPrintStatementNode* node, std::vector<IRExpressionNode*> arguments);
    std::vector<IRExpressionNode*>* getIRArguments();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_PRINT_STATEMENT_NODE_H
