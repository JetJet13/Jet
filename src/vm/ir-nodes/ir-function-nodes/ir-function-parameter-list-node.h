// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
