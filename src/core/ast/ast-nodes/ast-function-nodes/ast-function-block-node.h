//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_FUNCTION_BLOCK_NODE_H
#define JETLANG_AST_FUNCTION_BLOCK_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-expression-nodes/ast-function-return-expression-node.h"
#include "../ast-block-nodes/ast-block-start-node.h"
#include "../ast-block-nodes/ast-block-end-node.h"

class ASTFunctionBlockNode : public ASTNode {
private:
    std::shared_ptr<ASTBlockStartNode> _blockStartNode;
    std::shared_ptr<ASTBlockEndNode> _blockEndNode;
    std::vector<std::shared_ptr<ASTNode>> _contents;
    std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>> _returnStatements;
public:
    explicit ASTFunctionBlockNode(std::shared_ptr<ASTBlockStartNode> blockStartNode, std::vector<std::shared_ptr<ASTNode>> contents, std::shared_ptr<ASTBlockEndNode> blockEndNode);
    std::vector<std::shared_ptr<ASTNode>>* getContents();
    std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* getReturnStatements();
    bool hasReturnExpression();
    std::shared_ptr<ASTBlockStartNode> getStartNode();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    std::string toString() override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_BLOCK_NODE_H
