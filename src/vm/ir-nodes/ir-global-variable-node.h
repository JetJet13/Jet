//
// Created by Johny Georges on 2024-07-25.
//

#ifndef JETLANG_IR_GLOBAL_VARIABLE_NODE_H
#define JETLANG_IR_GLOBAL_VARIABLE_NODE_H

#include "ir-node.h"
#include "ir-instruction-node.h"
#include "../ir-type/ir-pointer-type.h"

class IRGlobalVariableNode : public IRNode {
private:
    llvm::GlobalVariable* _irValue;
    std::optional<IRGlobalVariableNode*> _parentGlobalVariable;
    std::vector<IRGlobalVariableNode*> _childGlobalVariables;
    std::unordered_map<std::string, IRGlobalVariableNode*> _childGlobalVariableMap;
    IRPointerType* _type;
public:
    IRGlobalVariableNode(llvm::GlobalVariable* irValue, IRPointerType* irType, std::vector<IRGlobalVariableNode*> childGlobalVariables);
    IRGlobalVariableNode(llvm::GlobalVariable* irValue, IRPointerType* irType, std::unordered_map<std::string, IRGlobalVariableNode*> childGlobalVariableMap);
    IRGlobalVariableNode(llvm::GlobalVariable* irValue, IRPointerType* type, IRGlobalVariableNode* parentGlobalVariable);
    IRGlobalVariableNode(llvm::GlobalVariable* irValue, IRPointerType* type);

    llvm::GlobalVariable* getValue();
    std::optional<IRGlobalVariableNode*> getParent();
    std::vector<IRGlobalVariableNode*>* getChildGlobalVariables();
    bool hasChildGlobalVariableMap();
    IRGlobalVariableNode* getChildGlobalVariableForKey(std::string key);
    IRPointerType* getIRType();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_GLOBAL_VARIABLE_NODE_H
