//
// Created by Johny Georges on 2024-07-08.
//

#ifndef JETLANG_IR_FUNCTION_DECLARATION_NODE_H
#define JETLANG_IR_FUNCTION_DECLARATION_NODE_H

#include <llvm/IR/Function.h>
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../ir-block-nodes/ir-block-node.h"
#include "../ir-function-nodes/ir-function-parameter-list-node.h"
#include "ir-declaration-node.h"
#include "../../ir-lookup-table/ir-lookup-table.h"

class IRFunctionDeclarationNode : public IRDeclarationNode {
private:
    std::shared_ptr<ASTFunctionDeclarationNode> _node;
    llvm::Function* _irValue;
    std::shared_ptr<IRFunctionParameterListNode> _irParameterList;
    std::shared_ptr<IRBlockNode> _irBlock;
    std::shared_ptr<IRInstructionNode> _globalVariable;
public:
    IRFunctionDeclarationNode(std::shared_ptr<ASTFunctionDeclarationNode> node, llvm::Function* irValue, std::shared_ptr<IRFunctionParameterListNode> irParameterList, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInstructionNode> globalVariable);
    std::string getName();
    std::string getNormalizedName();
    std::shared_ptr<IRFunctionParameterListNode> getParameters();
    std::shared_ptr<IRInstructionNode> getGlobalVariable();
    std::shared_ptr<IRBlockNode> getBlock();
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_DECLARATION_NODE_H
