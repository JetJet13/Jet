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
    ASTFinallyNode* _finallyKeyword;
    ASTControlFlowBlockNode* _block;
public:
    explicit ASTFinallyBlockNode(ASTFinallyNode* finallyKeyword, ASTControlFlowBlockNode* block);
    ASTControlFlowBlockNode* getBlock();
    std::vector<ASTFunctionReturnExpressionNode*>* getReturnStatements() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FINALLY_BLOCK_NODE_H
