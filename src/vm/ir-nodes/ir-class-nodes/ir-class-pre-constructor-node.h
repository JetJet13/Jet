//
// Created by Johny Georges on 2025-12-27.
//

#ifndef JETLANG_IR_CLASS_PRE_CONSTRUCTOR_NODE_H
#define JETLANG_IR_CLASS_PRE_CONSTRUCTOR_NODE_H

#include <vector>
#include <llvm/IR/Function.h>
#include "../ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../ir-lookup-table/ir-lookup-table.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-constructor-declaration-node.h"
#include "../ir-function-nodes/ir-function-parameter-list-node.h"

class IRClassPreConstructorNode {
private:
    llvm::Function* _irValue;
    IRBlockNode* _irBlock;
    IRInstructionNode* _classScopeParameter;
    std::unordered_map<unsigned long, IRExpressionNode*>* _irExpressions;
public:
    IRClassPreConstructorNode(llvm::Function* irValue, IRInstructionNode* classScopeParameter, std::unordered_map<unsigned long, IRExpressionNode*>* irExpressions, IRBlockNode* irBlock);
    llvm::Function* getFunction();
    std::unordered_map<unsigned long, IRExpressionNode*>* getExpressions();
    IRInstructionNode* getClassScopeParameter();
    IRBlockNode* getBlock();
    IRLookupTable* getScope();
};

#endif //JETLANG_IR_CLASS_PRE_CONSTRUCTOR_NODE_H
