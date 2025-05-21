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
    ASTIfStatementNode* _node;
    IRIfElseNode* _ifElseNode;
    std::optional<IRBlockNode*> _parentBlock;
public:
    IRIfStatementNode(ASTIfStatementNode* node, IRIfElseNode* ifElseNode);
    IRIfElseNode* getIfElseNode();
    std::optional<IRBlockNode*> getParentBlock();
    void setParentBlock(IRBlockNode* parentIRBlock);
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_IF_STATEMENT_NODE_H
