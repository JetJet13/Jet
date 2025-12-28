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
    ASTClassConstructorDeclarationNode* _node;
    llvm::Function* _irValue;
    IRBlockNode* _irBlock;
    IRFunctionParameterListNode* _irParameters;
    IRLookupTable* _scope;

public:
    IRClassConstructorNode(ASTClassConstructorDeclarationNode* node, llvm::Function* irValue, IRFunctionParameterListNode* irParameters, IRBlockNode* irBlock, IRLookupTable* scope);
    ASTClassConstructorDeclarationNode* getNode();
    llvm::Function* getFunction();
    IRFunctionParameterListNode* getParameters();
    IRBlockNode* getBlock();
    IRLookupTable* getScope();
};


#endif //JETLANG_IR_CLASS_CONSTRUCTOR_NODE_H
