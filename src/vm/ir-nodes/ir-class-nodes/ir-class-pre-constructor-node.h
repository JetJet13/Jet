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
    std::vector<std::pair<unsigned long, IRExpressionNode*>>* _irExpressions;
    std::vector<std::pair<unsigned long, llvm::Constant*>>* _irInitializers;
public:
    IRClassPreConstructorNode(llvm::Function* irValue, IRInstructionNode* classScopeParameter, std::vector<std::pair<unsigned long, IRExpressionNode*>>* irExpressions, std::vector<std::pair<unsigned long, llvm::Constant*>>* irInitializers, IRBlockNode* irBlock);
    llvm::Function* getFunction();
    std::vector<std::pair<unsigned long, IRExpressionNode*>>* getExpressions();
    std::vector<std::pair<unsigned long, llvm::Constant*>>* getInitializers();
    IRInstructionNode* getClassScopeParameter();
    IRBlockNode* getBlock();
    IRLookupTable* getScope();
};

#endif //JETLANG_IR_CLASS_PRE_CONSTRUCTOR_NODE_H
