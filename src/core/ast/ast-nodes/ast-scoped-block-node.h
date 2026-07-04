//
// Created by Johny Georges on 2024-05-23.
//

#ifndef JETLANG_AST_SCOPED_BLOCK_NODE_H
#define JETLANG_AST_SCOPED_BLOCK_NODE_H

#include "ast-node.h"
#include "ast-expression-nodes/ast-function-return-expression-node.h"

class ASTScopedBlockNode : public ASTNode {
public:
    bool isScopedBlockNode() override;
    virtual std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* getReturnStatements() = 0;
};

#endif //JETLANG_AST_SCOPED_BLOCK_NODE_H
