//
// Created by Johny Georges on 2024-04-01.
//

#ifndef JETLANG_AST_CATCH_BLOCK_NODE_H
#define JETLANG_AST_CATCH_BLOCK_NODE_H

#include "../../ast-node.h"
#include "../../ast-type-nodes/ast-type-node.h"
#include "../ast-control-flow-condition-node.h"
#include "../ast-control-flow-block-node.h"
#include "ast-catch-error-variable-node.h"

class ASTCatchBlockNode : public ASTNode {
private:
    ASTControlFlowBlockNode* _block;
    std::optional<ASTCatchErrorVariableNode*> _errorVariable;
public:
    explicit ASTCatchBlockNode(ASTControlFlowBlockNode* block, std::optional<ASTCatchErrorVariableNode*> errorVariable = {});
    ASTControlFlowBlockNode* getBlock();
    std::optional<ASTCatchErrorVariableNode*> getErrorVariable();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CATCH_BLOCK_NODE_H
