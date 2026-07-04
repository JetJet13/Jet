//
// Created by Johny Georges on 2025-05-24.
//

#ifndef JETLANG_IR_FOR_IN_STATEMENT_NODE_H
#define JETLANG_IR_FOR_IN_STATEMENT_NODE_H

#include "../ir-statement-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-for-in-statement-node.h"
#include "../../ir-block-nodes/ir-block-node.h"
#include "../../ir-captured-variable-node.h"
#include "../../../ir-lookup-table/ir-lookup-table.h"

class IRForInStatementNode : public IRStatementNode {
private:
    std::shared_ptr<ASTForInStatementNode> _node;
    IRInstructionNode* _index;
    IRInstructionNode* _variable;
    IRExpressionNode* _source;
    IRBlockNode* _setupBlock;
    IRBlockNode* _forInBlock;
    IRBlockNode* _bodyBlock;
    IRBlockNode* _endBlock;
    std::optional<IRCapturedVariableNode*> _capturedVariable;
public:
    IRForInStatementNode(std::shared_ptr<ASTForInStatementNode> node, IRInstructionNode* index, IRInstructionNode* variable, IRExpressionNode* source, IRBlockNode* setupBlock, IRBlockNode* forInBlock, IRBlockNode* bodyBlock, IRBlockNode* endBlock, std::optional<IRCapturedVariableNode*> capturedVariable = {});
    IRInstructionNode* getIndex();
    IRInstructionNode* getVariable();
    std::optional<IRCapturedVariableNode*> getCapturedVariable();
    IRExpressionNode* getSource();
    IRBlockNode* getSetupBlock();
    IRBlockNode* getForInBlock();
    IRBlockNode* getBodyBlock();
    IRBlockNode* getEndBlock();
    void nestIn(IRBlockNode* irBlock);
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FOR_IN_STATEMENT_NODE_H
