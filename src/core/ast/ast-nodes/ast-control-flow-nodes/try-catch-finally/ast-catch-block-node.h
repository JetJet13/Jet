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
    std::shared_ptr<ASTCatchNode> _catchKeyword;
    std::shared_ptr<ASTControlFlowBlockNode> _block;
    std::optional<std::shared_ptr<ASTCatchErrorVariableNode>> _errorVariable;
public:
    explicit ASTCatchBlockNode(std::shared_ptr<ASTCatchNode> catchKeyword, std::shared_ptr<ASTControlFlowBlockNode> block, std::optional<std::shared_ptr<ASTCatchErrorVariableNode>> errorVariable = {});
    std::shared_ptr<ASTControlFlowBlockNode> getBlock();
    std::optional<std::shared_ptr<ASTCatchErrorVariableNode>> getErrorVariable();
    std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* getReturnStatements() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CATCH_BLOCK_NODE_H
