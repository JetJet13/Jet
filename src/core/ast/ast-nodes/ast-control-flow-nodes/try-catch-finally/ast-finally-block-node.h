//
// Created by Johny Georges on 2024-04-01.
//

#ifndef JETLANG_AST_FINALLY_BLOCK_NODE_H
#define JETLANG_AST_FINALLY_BLOCK_NODE_H

#include "../../ast-node.h"
#include "../../ast-type-nodes/ast-type-node.h"
#include "../ast-control-flow-condition-node.h"
#include "../ast-control-flow-block-node.h"
#include "ast-finally-node.h"

class ASTFinallyBlockNode : public ASTScopedBlockNode {
private:
    std::shared_ptr<ASTFinallyNode> _finallyKeyword;
    std::shared_ptr<ASTControlFlowBlockNode> _block;
public:
    explicit ASTFinallyBlockNode(std::shared_ptr<ASTFinallyNode> finallyKeyword, std::shared_ptr<ASTControlFlowBlockNode> block);
    std::shared_ptr<ASTControlFlowBlockNode> getBlock();
    std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* getReturnStatements() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FINALLY_BLOCK_NODE_H
