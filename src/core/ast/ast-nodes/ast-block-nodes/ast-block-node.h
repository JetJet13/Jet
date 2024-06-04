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
    ASTBlockStartNode* _blockStartNode;
    ASTBlockEndNode* _blockEndNode;
    std::vector<ASTNode*> _contents;
public:
    explicit ASTBlockNode(ASTBlockStartNode* blockStartNode, ASTBlockEndNode* blockEndNode);
    explicit ASTBlockNode(ASTBlockStartNode* blockStartNode, std::vector<ASTNode*> contents, ASTBlockEndNode* blockEndNode);
    ASTBlockNode* addContent(ASTNode* content);
    void hoistTypes(std::vector<ASTNodeType> astNodeTypes);
    unsigned long size();
    std::vector<ASTNode*>* getContents();
    ASTNode *transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    bool isSameAs(ASTNode* other) override;
    std::string toString() override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_BLOCK_NODE_H
