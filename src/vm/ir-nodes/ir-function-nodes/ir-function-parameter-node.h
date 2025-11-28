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
public:
    IRFunctionParameterNode(llvm::Argument* irValue, IRParameterType* parameterType, std::optional<ASTFunctionParameterNode*> node = {});
    llvm::Argument* getArgument();
    IRParameterType* getParameterType();
    bool needsToBeFreed();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_PARAMETER_NODE_H
