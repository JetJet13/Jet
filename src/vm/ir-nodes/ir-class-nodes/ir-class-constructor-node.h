//
// Created by Johny Georges on 2024-12-09.
//

#ifndef JETLANG_IR_CLASS_CONSTRUCTOR_NODE_H
#define JETLANG_IR_CLASS_CONSTRUCTOR_NODE_H

#include <llvm/IR/Function.h>
#include "../ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../ir-lookup-table/ir-lookup-table.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-constructor-declaration-node.h"
#include "../ir-function-nodes/ir-function-parameter-list-node.h"

class IRClassConstructorNode {
private:
    std::shared_ptr<ASTClassConstructorDeclarationNode> _node;
    llvm::Function* _irValue;
    std::shared_ptr<IRBlockNode> _irBlock;
    std::shared_ptr<IRFunctionParameterListNode> _irParameters;
public:
    IRClassConstructorNode(std::shared_ptr<ASTClassConstructorDeclarationNode> node, llvm::Function* irValue, std::shared_ptr<IRFunctionParameterListNode> irParameters, std::shared_ptr<IRBlockNode> irBlock);
    std::shared_ptr<ASTClassConstructorDeclarationNode> getNode();
    llvm::Function* getFunction();
    std::shared_ptr<IRFunctionParameterListNode> getParameters();
    std::shared_ptr<IRBlockNode> getBlock();
};


#endif //JETLANG_IR_CLASS_CONSTRUCTOR_NODE_H
