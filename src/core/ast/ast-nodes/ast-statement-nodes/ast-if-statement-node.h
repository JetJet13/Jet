//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_IF_STATEMENT_NODE_H
#define JETLANG_AST_IF_STATEMENT_NODE_H

#include "./ast-statement-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-assignment-node.h"
#include "../ast-control-flow-nodes/ast-if-block-node.h"
#include "../ast-control-flow-nodes/ast-else-if-block-node.h"
#include "../ast-control-flow-nodes/ast-else-block-node.h"

class ASTIfStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTIfBlockNode> _ifBlock;
    std::vector<std::shared_ptr<ASTElseIfBlockNode>> _elseIfBlocks;
    std::optional<std::shared_ptr<ASTElseBlockNode>> _elseBlock;
public:
    ASTIfStatementNode(std::shared_ptr<ASTIfBlockNode> ifBlock);
    ASTIfStatementNode(std::shared_ptr<ASTIfBlockNode> ifBlock, std::vector<std::shared_ptr<ASTElseIfBlockNode>> elseIfBlocks, std::optional<std::shared_ptr<ASTElseBlockNode>> elseBlock = {});
    std::shared_ptr<ASTIfStatementNode> addElseIfBlock(std::shared_ptr<ASTElseIfBlockNode> elseIfBlock);
    std::shared_ptr<ASTIfBlockNode> getIfBlock();
    std::vector<std::shared_ptr<ASTElseIfBlockNode>>* getElseIfBlocks();
    std::optional<std::shared_ptr<ASTElseBlockNode>> getElseBlock();
    bool onlyHasIfBlock();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IF_STATEMENT_NODE_H
