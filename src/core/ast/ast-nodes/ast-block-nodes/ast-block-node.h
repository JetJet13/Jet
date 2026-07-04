//
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_AST_BLOCK_NODE_H
#define JETLANG_AST_BLOCK_NODE_H

#include "../ast-expression-nodes/ast-expression-node.h"
#include "../../../pre-processor/syntax-analyzer/types/syntax-analyzer-mode.h"
#include "../ast-scoped-block-node.h"
#include "ast-block-start-node.h"
#include "ast-block-end-node.h"

class ASTBlockNode : public ASTScopedBlockNode {
private:
    std::shared_ptr<ASTBlockStartNode> _blockStartNode;
    std::shared_ptr<ASTBlockEndNode> _blockEndNode;
    std::vector<std::shared_ptr<ASTNode>> _contents;
public:
    explicit ASTBlockNode(std::shared_ptr<ASTBlockStartNode> blockStartNode, std::shared_ptr<ASTBlockEndNode> blockEndNode);
    explicit ASTBlockNode(std::shared_ptr<ASTBlockStartNode> blockStartNode, std::vector<std::shared_ptr<ASTNode>> contents, std::shared_ptr<ASTBlockEndNode> blockEndNode);
    std::shared_ptr<ASTBlockNode> addContent(std::shared_ptr<ASTNode> content);
    void hoistTypes(std::vector<ASTNodeType> astNodeTypes);
    unsigned long size();
    std::vector<std::shared_ptr<ASTNode>>* getContents();
    std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* getReturnStatements() override;
    std::shared_ptr<ASTNode> transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    std::string toString() override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_BLOCK_NODE_H
