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
    ASTBlockStartNode* _blockStartNode;
    ASTBlockEndNode* _blockEndNode;
    std::vector<ASTNode*> _contents;
    std::vector<ASTFunctionReturnExpressionNode*> _returnStatements;
public:
    explicit ASTControlFlowBlockNode(ASTBlockStartNode* blockStartNode, std::vector<ASTNode*> contents, ASTBlockEndNode* blockEndNode);
    std::vector<ASTNode*>* getContents();
    std::vector<ASTFunctionReturnExpressionNode*>* getReturnStatements() override;
    bool hasReturnExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    bool isSameAs(ASTNode* other) override;
    std::string toString() override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CONTROL_FLOW_BLOCK_NODE_H
