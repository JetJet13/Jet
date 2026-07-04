//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_CONTROL_FLOW_BLOCK_NODE_H
#define JETLANG_AST_CONTROL_FLOW_BLOCK_NODE_H

#include "../ast-scoped-block-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-expression-nodes/ast-function-return-expression-node.h"
#include "../ast-block-nodes/ast-block-end-node.h"
#include "../ast-block-nodes/ast-block-start-node.h"


class ASTControlFlowBlockNode : public ASTScopedBlockNode {
private:
    std::shared_ptr<ASTBlockStartNode> _blockStartNode;
    std::shared_ptr<ASTBlockEndNode> _blockEndNode;
    std::vector<std::shared_ptr<ASTNode>> _contents;
    std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>> _returnStatements;
public:
    explicit ASTControlFlowBlockNode(std::shared_ptr<ASTBlockStartNode> blockStartNode, std::vector<std::shared_ptr<ASTNode>> contents, std::shared_ptr<ASTBlockEndNode> blockEndNode);
    std::vector<std::shared_ptr<ASTNode>>* getContents();
    std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* getReturnStatements() override;
    bool hasReturnExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    std::string toString() override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CONTROL_FLOW_BLOCK_NODE_H
