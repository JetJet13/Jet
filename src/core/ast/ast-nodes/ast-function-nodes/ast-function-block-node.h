//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_FUNCTION_BLOCK_NODE_H
#define JETLANG_AST_FUNCTION_BLOCK_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-expression-nodes/ast-function-return-expression-node.h"

class ASTFunctionBlockNode : public ASTNode {
private:
    std::vector<ASTNode*> _contents;
public:
    explicit ASTFunctionBlockNode(std::vector<ASTNode*> contents);
    std::vector<ASTNode*> getContents();
    ASTNodeType getNodeType() override;
    bool isSameAs(ASTNode* other) override;
    std::string toString() override;
    void print() override;
};

#endif //JETLANG_AST_FUNCTION_BLOCK_NODE_H
