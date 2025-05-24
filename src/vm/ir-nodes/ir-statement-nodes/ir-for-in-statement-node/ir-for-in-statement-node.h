//
// Created by Johny Georges on 2025-05-24.
//

#ifndef JETLANG_IR_FOR_IN_STATEMENT_NODE_H
#define JETLANG_IR_FOR_IN_STATEMENT_NODE_H

#include "../ir-statement-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-for-in-statement-node.h"
#include "../../ir-block-node.h"

class IRForInStatementNode : public IRStatementNode {
private:
    ASTForInStatementNode* _node;
    IRInstructionNode* _index;
    IRInstructionNode* _variable;
    IRExpressionNode* _source;
    IRBlockNode* _setupBlock;
    IRBlockNode* _forInBlock;
    IRBlockNode* _bodyBlock;
    IRBlockNode* _endBlock;
public:
    IRForInStatementNode(ASTForInStatementNode* node, IRInstructionNode* index, IRInstructionNode* variable, IRExpressionNode* source, IRBlockNode* setupBlock, IRBlockNode* forInBlock, IRBlockNode* bodyBlock, IRBlockNode* endBlock);
    IRInstructionNode* getIndex();
    IRInstructionNode* getVariable();
    IRExpressionNode* getSource();
    IRBlockNode* getSetupBlock();
    IRBlockNode* getForInBlock();
    IRBlockNode* getBodyBlock();
    IRBlockNode* getEndBlock();
    void setBlocksToBeSuccessorsOf(IRBlockNode* irBlock);
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FOR_IN_STATEMENT_NODE_H
