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
#include "ast-catch-node.h"

class ASTCatchBlockNode : public ASTScopedBlockNode {
private:
    ASTCatchNode* _catchKeyword;
    ASTControlFlowBlockNode* _block;
    std::optional<ASTCatchErrorVariableNode*> _errorVariable;
public:
    explicit ASTCatchBlockNode(ASTCatchNode* catchKeyword, ASTControlFlowBlockNode* block, std::optional<ASTCatchErrorVariableNode*> errorVariable = {});
    ASTControlFlowBlockNode* getBlock();
    std::optional<ASTCatchErrorVariableNode*> getErrorVariable();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CATCH_BLOCK_NODE_H
