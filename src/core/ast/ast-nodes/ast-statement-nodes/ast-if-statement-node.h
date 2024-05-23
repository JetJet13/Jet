//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_IF_STATEMENT_NODE_H
#define JETLANG_AST_IF_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-assignment-node.h"
#include "../ast-control-flow-nodes/ast-if-block-node.h"
#include "../ast-control-flow-nodes/ast-else-if-block-node.h"
#include "../ast-control-flow-nodes/ast-else-block-node.h"

class ASTIfStatementNode : public ASTStatementNode {
private:
    ASTIfBlockNode* _ifBlock;
    std::vector<ASTElseIfBlockNode*> _elseIfBlocks;
    std::optional<ASTElseBlockNode*> _elseBlock;
public:
    ASTIfStatementNode(ASTIfBlockNode* ifBlock);
    ASTIfStatementNode(ASTIfBlockNode* ifBlock, std::vector<ASTElseIfBlockNode*> elseIfBlocks, std::optional<ASTElseBlockNode*> elseBlock = {});
    ASTIfStatementNode* addElseIfBlock(ASTElseIfBlockNode* elseIfBlock);
    ASTIfBlockNode* getIfBlock();
    std::vector<ASTElseIfBlockNode*>* getElseIfBlocks();
    std::optional<ASTElseBlockNode*> getElseBlock();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_IF_STATEMENT_NODE_H
