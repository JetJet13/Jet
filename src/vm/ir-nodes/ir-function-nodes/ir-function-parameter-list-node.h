//
// Created by Johny Georges on 2024-07-08.
//

#ifndef JETLANG_IR_FUNCTION_PARAMETER_LIST_NODE_H
#define JETLANG_IR_FUNCTION_PARAMETER_LIST_NODE_H

#include <llvm/IR/Argument.h>
#include "../../../core/ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ir-node.h"

class IRFunctionParameterListNode : public IRNode {
private:
    ASTFunctionParameterListNode* _node;
    std::vector<llvm::Argument*> _irValues;
public:
    IRFunctionParameterListNode(ASTFunctionParameterListNode* node, std::vector<llvm::Argument*> irValues);
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_PARAMETER_LIST_NODE_H
