//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_AST_FOR_STATEMENT_NODE_H
#define JETLANG_AST_FOR_STATEMENT_NODE_H

#include <vector>
#include "./ast-statement-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-control-flow-nodes/ast-for-variable-node.h"
#include "../ast-control-flow-nodes/ast-for-source-node.h"
#include "../ast-control-flow-nodes/ast-control-flow-block-node.h"
#include "../ast-control-flow-nodes/ast-for-node.h"
#include "../ast-control-flow-nodes/ast-for-in-node.h"

class ASTForStatementNode : public ASTStatementNode {
private:
    ASTForNode* _forKeyword;
    ASTForVariableNode* _variable;
    ASTForInNode* _inKeyword;
    ASTForSourceNode* _source;
    ASTControlFlowBlockNode* _block;
public:
    explicit ASTForStatementNode(ASTForNode* forKeyword, ASTForVariableNode* variable, ASTForInNode* inKeyword, ASTForSourceNode* source, ASTControlFlowBlockNode* block);
    ASTForVariableNode* getVariable();
    ASTForSourceNode* getSource();
    ASTControlFlowBlockNode* getBlock();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FOR_STATEMENT_NODE_H
