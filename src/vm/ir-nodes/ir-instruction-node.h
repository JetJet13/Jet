//
// Created by Johny Georges on 2024-07-25.
//

#ifndef JETLANG_IR_INSTRUCTION_NODE_H
#define JETLANG_IR_INSTRUCTION_NODE_H

#include <unordered_map>
#include "ir-node.h"
#include "../ir-type/ir-type.h"
#include "../ir-type/ir-pointer-type.h"

// forward declaration
class IRBlockNode;

class IRInstructionNode : public IRNode {
protected:
    llvm::Value* _irValue;
    std::vector<llvm::Value*> _ancestorValues;
    std::vector<llvm::Value*> _descendentValues;
    std::optional<IRInstructionNode*> _parentAllocation;
    std::vector<IRInstructionNode*> _childAllocations;
    std::unordered_map<std::string, IRInstructionNode*> _childAllocationMap;
    std::shared_ptr<IRPointerType> _irType;
    bool _isGlobal = false;
public:
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, IRInstructionNode* parentAllocation, std::vector<IRInstructionNode*> childAllocations);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::optional<IRInstructionNode*> parentAllocation);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::optional<IRInstructionNode*> parentAllocation);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<IRInstructionNode*> childAllocations);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::vector<IRInstructionNode*> childAllocations);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::vector<llvm::Value*> descendentValues);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::unordered_map<std::string, IRInstructionNode*> childAllocationMap);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::unordered_map<std::string, IRInstructionNode*> childAllocationMap);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType);
    bool isGlobal();
    void markAsGlobal();
    bool isInserted();
    bool isValueGlobalVariable();
    llvm::Value* getValue();
    llvm::Type* getAllocatedType();
    std::vector<llvm::Value*>* getAncestorValues();
    std::vector<llvm::Value*>* getDescendentValues();
    std::optional<IRInstructionNode*> getParentAllocation();
    std::vector<IRInstructionNode*>* getChildAllocations();
    void insertAncestorValue(llvm::Value* ancestorValue);
    void insertDescendentValue(llvm::Value* descendentValue);
    bool hasChildAllocationMap();
    IRInstructionNode* getChildAllocationForKey(std::string key);
    void setParentAllocation(std::optional<IRInstructionNode*> parentAllocation);
    llvm::MaybeAlign getAlignment();
    uint64_t getSizeInBytes();
    std::shared_ptr<IRPointerType> getIRType();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void printChildAllocations();
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_INSTRUCTION_NODE_H
