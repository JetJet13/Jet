//
// Created by Johny Georges on 2024-07-08.
//

#ifndef JETLANG_IR_FUNCTION_PARAMETER_LIST_NODE_H
#define JETLANG_IR_FUNCTION_PARAMETER_LIST_NODE_H

#include <llvm/IR/Argument.h>
#include "../../../core/ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ir-node.h"
#include "../../ir-type/ir-parameter-type.h"
#include "ir-function-parameter-node.h"

class IRFunctionParameterListNode : public IRNode {
private:
    ASTFunctionParameterListNode* _node;
    std::vector<IRFunctionParameterNode*> _parameters;

public:
    IRFunctionParameterListNode(ASTFunctionParameterListNode* node, std::vector<IRFunctionParameterNode*> parameters);
    void addScopeParameter(IRFunctionParameterNode* parameter);
    std::vector<IRFunctionParameterNode*>* getParameters();
    std::vector<llvm::Argument*> getArguments();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_PARAMETER_LIST_NODE_H
