//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_AST_FOR_IN_STATEMENT_NODE_H
#define JETLANG_AST_FOR_IN_STATEMENT_NODE_H

#include <vector>
#include "./ast-statement-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-control-flow-nodes/ast-for-in-variable-node.h"
#include "../ast-control-flow-nodes/ast-for-in-source-node.h"
#include "../ast-control-flow-nodes/ast-control-flow-block-node.h"
#include "../ast-control-flow-nodes/ast-for-node.h"
#include "../ast-control-flow-nodes/ast-for-in-node.h"

class ASTForInStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTForNode> _forKeyword;
    std::shared_ptr<ASTForInVariableNode> _variable;
    std::shared_ptr<ASTForInNode> _inKeyword;
    std::shared_ptr<ASTForInSourceNode> _source;
    std::shared_ptr<ASTControlFlowBlockNode> _block;
public:
    explicit ASTForInStatementNode(std::shared_ptr<ASTForNode> forKeyword, std::shared_ptr<ASTForInVariableNode> variable, std::shared_ptr<ASTForInNode> inKeyword, std::shared_ptr<ASTForInSourceNode> source, std::shared_ptr<ASTControlFlowBlockNode> block);
    std::shared_ptr<ASTForInVariableNode> getVariable();
    std::shared_ptr<ASTForInSourceNode> getSource();
    std::shared_ptr<ASTControlFlowBlockNode> getBlock();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FOR_IN_STATEMENT_NODE_H
