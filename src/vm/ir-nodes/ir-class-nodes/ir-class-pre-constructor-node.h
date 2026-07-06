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
    std::shared_ptr<IRBlockNode> _irBlock;
    std::shared_ptr<IRInstructionNode> _classScopeParameter;
    std::vector<std::pair<unsigned long, std::shared_ptr<IRExpressionNode>>>* _irExpressions;
    std::vector<std::pair<unsigned long, llvm::Constant*>>* _irInitializers;
public:
    IRClassPreConstructorNode(llvm::Function* irValue, std::shared_ptr<IRInstructionNode> classScopeParameter, std::vector<std::pair<unsigned long, std::shared_ptr<IRExpressionNode>>>* irExpressions, std::vector<std::pair<unsigned long, llvm::Constant*>>* irInitializers, std::shared_ptr<IRBlockNode> irBlock);
    llvm::Function* getFunction();
    std::vector<std::pair<unsigned long, std::shared_ptr<IRExpressionNode>>>* getExpressions();
    std::vector<std::pair<unsigned long, llvm::Constant*>>* getInitializers();
    std::shared_ptr<IRInstructionNode> getClassScopeParameter();
    std::shared_ptr<IRBlockNode> getBlock();
    std::shared_ptr<IRLookupTable> getScope();
};

#endif //JETLANG_IR_CLASS_PRE_CONSTRUCTOR_NODE_H
