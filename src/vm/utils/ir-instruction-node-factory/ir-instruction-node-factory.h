//
// Created by Johny Georges on 2024-07-27.
//

#ifndef JETLANG_IR_INSTRUCTION_NODE_FACTORY_H
#define JETLANG_IR_INSTRUCTION_NODE_FACTORY_H

#include "../../ir-nodes/ir-instruction-node.h"
#include "../../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../../ir-type/ir-array-pointer-type.h"

class IRInstructionNodeFactory {
public:
    static IRInstructionNode* create(llvm::GlobalVariable* globalVariable);
    static IRInstructionNode* create(llvm::GlobalVariable* globalVariable, IRPointerType* irType, std::optional<IRInstructionNode*> sourceAllocation);
    static IRInstructionNode* create(llvm::Value* irValue, IRPointerType* irType);
    static IRInstructionNode* create(llvm::Value* irValue, IRPointerType* irType, std::vector<llvm::Value*> ancestorValues);
    static IRInstructionNode* create(llvm::Value* irValue, IRPointerType* irType, std::vector<IRInstructionNode*> childAllocations);
    static IRInstructionNode* create(llvm::Value* irValue, IRPointerType* irType, std::vector<llvm::Value*> ancestorValues, std::vector<IRInstructionNode*> childAllocations);
    static IRInstructionNode* create(llvm::Value* irValue, IRPointerType* irType, std::vector<llvm::Value*> ancestorValues, IRInstructionNode* sourceInstructionNode);
    static IRInstructionNode* create(llvm::Value* irValue, IRPointerType* irType, IRInstructionNode* sourceInstructionNode);
    static IRInstructionNode* create(IRInstructionNode* otherInstructionNode);
    static IRInstructionNode* create(IRInstructionNode* otherInstructionNode, IRInstructionNode* sourceInstructionNode);
    static IRInstructionNode* create(IRPointerType* irType);
    static IRInstructionNode* create(IRPointerType* irType, std::unordered_map<std::string, IRInstructionNode*> childAllocationMap);
    static IRInstructionNode* create(IRPointerType* irType, llvm::Value* numElements);
    static IRInstructionNode* create(IRPointerType* irType, IRInstructionNode* sourceAllocation);
    static IRInstructionNode* create(IRPointerType* irType, std::vector<IRInstructionNode*> childAllocations);
    static IRInstructionNode* create(IRType* irType, IRInstructionNode* sourceAllocation);
    static IRInstructionNode* create(IRType* irType);
    static IRInstructionNode* create(IRPointerType* irType, std::string name);
    static IRInstructionNode* create(IRPointerType* irType, std::string name, std::optional<IRInstructionNode*> sourceAllocation);
};

#endif //JETLANG_IR_INSTRUCTION_NODE_FACTORY_H
