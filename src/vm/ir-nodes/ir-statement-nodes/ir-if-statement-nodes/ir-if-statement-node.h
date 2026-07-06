//
// Created by Johny Georges on 2025-01-08.
//

#ifndef JETLANG_IR_IF_STATEMENT_NODE_H
#define JETLANG_IR_IF_STATEMENT_NODE_H

#include "../../ir-expression-nodes/ir-expression-node.h"
#include "../ir-statement-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-if-statement-node.h"
#include "ir-if-else-node.h"

class IRIfStatementNode : public IRStatementNode {
private:
    std::shared_ptr<ASTIfStatementNode> _node;
    std::shared_ptr<IRIfElseNode> _ifElseNode;
    std::optional<std::shared_ptr<IRBlockNode>> _elseNode;
public:
    IRIfStatementNode(std::shared_ptr<ASTIfStatementNode> node, std::shared_ptr<IRIfElseNode> ifElseNode, std::optional<std::shared_ptr<IRBlockNode>> elseNode = {});
    std::shared_ptr<IRIfElseNode> getIfElseNode();
    std::optional<std::shared_ptr<IRBlockNode>> getElseNode();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_IF_STATEMENT_NODE_H
