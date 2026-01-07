//
// Created by Johny Georges on 2024-07-13.
//

#ifndef JETLANG_IR_FUNCTION_PARAMETER_NODE_H
#define JETLANG_IR_FUNCTION_PARAMETER_NODE_H

#include <llvm/IR/Argument.h>
#include "../ir-node.h"
#include "../../ir-type/ir-parameter-type.h"
#include "../../../core/ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"

class IRFunctionParameterNode : public IRNode {
private:
    llvm::Argument* _irValue;
    IRParameterType* _parameterType;
    std::optional<ASTFunctionParameterNode*> _node;
    IRInstructionNode* _allocation;
    std::optional<IRInstructionNode*> _irArc;
public:
    IRFunctionParameterNode(llvm::Argument* irValue, IRParameterType* parameterType, IRInstructionNode* allocation, std::optional<ASTFunctionParameterNode*> node = {}, std::optional<IRInstructionNode*> irArc = {});
    llvm::Argument* getArgument();
    IRParameterType* getParameterType();
    IRInstructionNode* getAllocation();
    std::optional<IRInstructionNode*> getArc();
    bool isCaptured();
    unsigned long getCaptureCount();
    bool needsToBeFreed();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_PARAMETER_NODE_H
