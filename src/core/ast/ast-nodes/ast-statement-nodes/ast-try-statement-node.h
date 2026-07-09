//
// Created by Johny Georges on 2024-04-01.
//

#ifndef JETLANG_AST_TRY_STATEMENT_NODE_H
#define JETLANG_AST_TRY_STATEMENT_NODE_H

#include "./ast-statement-node.h"
#include "../ast-control-flow-nodes/try-catch-finally/ast-try-block-node.h"
#include "../ast-control-flow-nodes/try-catch-finally/ast-catch-block-node.h"
#include "../ast-control-flow-nodes/try-catch-finally/ast-finally-block-node.h"

class ASTTryStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTTryBlockNode> _tryBlock;
    std::shared_ptr<ASTCatchBlockNode> _catchBlock;
    std::optional<std::shared_ptr<ASTFinallyBlockNode>> _finallyBlock;
public:
    ASTTryStatementNode(std::shared_ptr<ASTTryBlockNode> tryBlock, std::shared_ptr<ASTCatchBlockNode> catchBlock);
    ASTTryStatementNode(std::shared_ptr<ASTTryBlockNode> tryBlock, std::shared_ptr<ASTCatchBlockNode> catchBlock, std::shared_ptr<ASTFinallyBlockNode> finallyBlock);
    std::shared_ptr<ASTTryBlockNode> getTryBlock();
    std::shared_ptr<ASTCatchBlockNode> getCatchBlock();
    std::optional<std::shared_ptr<ASTFinallyBlockNode>> getFinallyBlock();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TRY_STATEMENT_NODE_H
