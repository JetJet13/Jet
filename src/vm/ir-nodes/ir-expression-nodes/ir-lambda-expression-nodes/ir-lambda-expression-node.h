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
// Created by Johny Georges on 2025-12-31.
//

#ifndef JETLANG_IR_LAMBDA_EXPRESSION_NODE_H
#define JETLANG_IR_LAMBDA_EXPRESSION_NODE_H

#include "../ir-expression-node.h"
#include "../../ir-function-nodes/ir-function-parameter-list-node.h"
#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-type/ir-lambda-type.h"

class IRLambdaExpressionNode : public IRExpressionNode {
public:
    std::shared_ptr<IRLambdaType> getIRLambdaType();
    virtual std::shared_ptr<IRInstructionNode> getAllocation() = 0;
    virtual llvm::Function* getFunctionValue() = 0;
    virtual std::shared_ptr<IRType> getIRType() = 0;
    virtual llvm::Function* getCleanupFunction() = 0;
    virtual std::shared_ptr<IRFunctionParameterListNode> getParameters() = 0;
    virtual std::shared_ptr<IRBlockNode> getBlock() = 0;
};

#endif //JETLANG_IR_LAMBDA_EXPRESSION_NODE_H
