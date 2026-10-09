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
// Created by Johny Georges on 2026-02-09.
//

#ifndef JETLANG_IR_FUNCTION_ARGUMENT_NODE_H
#define JETLANG_IR_FUNCTION_ARGUMENT_NODE_H

#include <llvm/IR/Argument.h>
#include "../ir-node.h"
#include "../../ir-type/ir-parameter-type.h"
#include "../../../core/ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"
#include "../ir-expression-nodes/ir-expression-node.h"
#include "../../ir-operation/ir-operation.h"

class IRFunctionArgumentNode : public IRNode {
private:
    std::shared_ptr<IRExpressionNode> _irArgument;
    std::shared_ptr<IROperation> _irOperation;
    std::optional<std::shared_ptr<ParameterListItemTypeSignature>> _parameterTypeSignature;
    void initIROperation();
public:
    IRFunctionArgumentNode(std::shared_ptr<IRExpressionNode> irArgument);
    IRFunctionArgumentNode(std::shared_ptr<IRExpressionNode> irArgument, std::shared_ptr<IROperation> irOperation);
    IRFunctionArgumentNode(std::shared_ptr<IRExpressionNode> irArgument, std::shared_ptr<ParameterListItemTypeSignature> parameterTypeSignature);
    std::shared_ptr<IRExpressionNode> getArgument();
    std::shared_ptr<IROperation> getOperation();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_ARGUMENT_NODE_H
