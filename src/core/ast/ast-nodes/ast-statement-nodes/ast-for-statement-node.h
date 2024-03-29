//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_AST_FOR_STATEMENT_NODE_H
#define JETLANG_AST_FOR_STATEMENT_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-type-node.h"
#include "../ast-control-flow-nodes/ast-for-variable-node.h"
#include "../ast-control-flow-nodes/ast-for-source-node.h"
#include "../ast-control-flow-nodes/ast-control-flow-block-node.h"

class ASTForStatementNode : public ASTNode {
private:
    ASTForVariableNode* _variable;
    ASTForSourceNode* _source;
    ASTControlFlowBlockNode* _block;
public:
    explicit ASTForStatementNode(ASTForVariableNode* variable, ASTForSourceNode* source, ASTControlFlowBlockNode* block);
    ASTForVariableNode* getVariable();
    ASTForSourceNode* getSource();
    ASTControlFlowBlockNode* getBlock();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FOR_STATEMENT_NODE_H
