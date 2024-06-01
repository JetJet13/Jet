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
    ASTTryBlockNode* _tryBlock;
    ASTCatchBlockNode* _catchBlock;
    std::optional<ASTFinallyBlockNode*> _finallyBlock;
public:
    ASTTryStatementNode(ASTTryBlockNode* tryBlock, ASTCatchBlockNode* catchBlock);
    ASTTryStatementNode(ASTTryBlockNode* tryBlock, ASTCatchBlockNode* catchBlock, ASTFinallyBlockNode* finallyBlock);
    ASTTryBlockNode* getTryBlock();
    ASTCatchBlockNode* getCatchBlock();
    std::optional<ASTFinallyBlockNode*> getFinallyBlock();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TRY_STATEMENT_NODE_H
