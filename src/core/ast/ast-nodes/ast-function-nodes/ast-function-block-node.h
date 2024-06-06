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
    ASTBlockStartNode* _blockStartNode;
    ASTBlockEndNode* _blockEndNode;
    std::vector<ASTNode*> _contents;
public:
    explicit ASTFunctionBlockNode(ASTBlockStartNode* blockStartNode, std::vector<ASTNode*> contents, ASTBlockEndNode* blockEndNode);
    std::vector<ASTNode*>* getContents();
    bool hasReturnExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    bool isSameAs(ASTNode* other) override;
    std::string toString() override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_BLOCK_NODE_H
