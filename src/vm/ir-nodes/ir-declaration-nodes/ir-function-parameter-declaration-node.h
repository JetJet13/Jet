//
// Created by Johny Georges on 2024-07-13.
//

#ifndef JETLANG_IR_FUNCTION_PARAMETER_DECLARATION_NODE_H
#define JETLANG_IR_FUNCTION_PARAMETER_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-declaration-node.h"
#include "../ir-function-nodes/ir-function-parameter-node.h"
#include "../ir-instruction-node.h"

class IRFunctionParameterDeclarationNode : public IRDeclarationNode {
private:
    llvm::Argument* _argument;
    IRInstructionNode* _irValue;
public:
    IRFunctionParameterDeclarationNode(llvm::Argument* argument, IRInstructionNode* irValue);
    void insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_PARAMETER_DECLARATION_NODE_H
