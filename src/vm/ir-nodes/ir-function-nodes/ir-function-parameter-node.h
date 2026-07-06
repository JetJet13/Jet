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
    std::shared_ptr<IRParameterType> _parameterType;
    std::optional<std::shared_ptr<ASTFunctionParameterNode>> _node;
    std::shared_ptr<IRInstructionNode> _allocation;
    std::optional<std::shared_ptr<IRInstructionNode>> _irArc;
public:
    IRFunctionParameterNode(llvm::Argument* irValue, std::shared_ptr<IRParameterType> parameterType, std::shared_ptr<IRInstructionNode> allocation, std::optional<std::shared_ptr<ASTFunctionParameterNode>> node = {}, std::optional<std::shared_ptr<IRInstructionNode>> irArc = {});
    llvm::Argument* getArgument();
    std::shared_ptr<IRParameterType> getParameterType();
    std::shared_ptr<IRInstructionNode> getAllocation();
    std::optional<std::shared_ptr<IRInstructionNode>> getArc();
    bool isCaptured();
    unsigned long getCaptureCount();
    bool needsToBeFreed();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_PARAMETER_NODE_H
