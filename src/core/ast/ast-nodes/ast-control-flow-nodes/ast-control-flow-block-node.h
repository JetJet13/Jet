//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_CONTROL_FLOW_BLOCK_NODE_H
#define JETLANG_AST_CONTROL_FLOW_BLOCK_NODE_H

#include "../ast-scoped-block-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-expression-nodes/ast-function-return-expression-node.h"

class ASTControlFlowBlockNode : public ASTScopedBlockNode {
private:
    std::vector<ASTNode*> _contents;
public:
    explicit ASTControlFlowBlockNode(std::vector<ASTNode*> contents);
    std::vector<ASTNode*>* getContents();
    bool hasReturnExpression();
    ASTNodeType getNodeType() override;
    bool isSameAs(ASTNode* other) override;
    std::string toString() override;
    void print() override;
};

#endif //JETLANG_AST_CONTROL_FLOW_BLOCK_NODE_H
