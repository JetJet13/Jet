//
// Created by Johny Georges on 2024-12-09.
//

#ifndef JETLANG_IR_CLASS_METHOD_NODE_H
#define JETLANG_IR_CLASS_METHOD_NODE_H

#include <llvm/IR/Function.h>
#include "../ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../ir-lookup-table/ir-lookup-table.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-method-declaration-node.h"
#include "../ir-function-nodes/ir-function-parameter-list-node.h"

class IRClassMethodNode {
private:
    std::shared_ptr<ASTClassMethodDeclarationNode> _node;
    llvm::Function* _irValue;
    std::shared_ptr<IRBlockNode> _irBlock;
    std::shared_ptr<IRFunctionParameterListNode> _irParameters;
    std::shared_ptr<IRInstructionNode> _globalVariable;
public:
    IRClassMethodNode(std::shared_ptr<ASTClassMethodDeclarationNode> node, llvm::Function* irValue, std::shared_ptr<IRFunctionParameterListNode> irParameters, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInstructionNode> globalVariable);
    std::shared_ptr<ASTClassMethodDeclarationNode> getNode();
    llvm::Function* getFunction();
    std::shared_ptr<IRFunctionParameterListNode> getParameters();
    std::shared_ptr<IRInstructionNode> getGlobalVariable();
    std::shared_ptr<IRBlockNode> getBlock();

};

#endif //JETLANG_IR_CLASS_METHOD_NODE_H
