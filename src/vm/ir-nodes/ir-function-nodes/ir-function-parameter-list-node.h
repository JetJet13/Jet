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
    std::shared_ptr<ASTFunctionParameterListNode> _node;
    std::vector<std::shared_ptr<IRFunctionParameterNode>> _parameters;
    std::optional<std::shared_ptr<IRFunctionParameterNode>> _scopeParameter;
public:
    IRFunctionParameterListNode(std::shared_ptr<ASTFunctionParameterListNode> node, std::vector<std::shared_ptr<IRFunctionParameterNode>> parameters);
    void addLambdaScopeParameter(std::shared_ptr<IRFunctionParameterNode> parameter);
    void addClassScopeParameter(std::shared_ptr<IRFunctionParameterNode> classScopeParameter);
    std::optional<std::shared_ptr<IRFunctionParameterNode>> getLambdaScopeParameter();
    std::vector<std::shared_ptr<IRFunctionParameterNode>>* getParameters();
    std::vector<llvm::Argument*> getArguments();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_PARAMETER_LIST_NODE_H
