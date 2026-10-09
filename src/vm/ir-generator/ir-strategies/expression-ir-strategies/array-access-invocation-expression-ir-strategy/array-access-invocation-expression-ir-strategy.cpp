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
// Created by Johny Georges on 2026-02-06.
//

#include "array-access-invocation-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-access-invocation-expression-node.h"

std::shared_ptr<IRExpressionNode> ArrayAccessInvocationExpressionIRStrategy::generate(std::shared_ptr<ASTArrayAccessInvocationExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto arguments = std::vector<std::shared_ptr<IRFunctionArgumentNode>>();
    for (int i = 0; i < node->getArguments()->numArguments(); ++i) {
        auto argument = node->getArguments()->getArguments()->at(i);
        arguments.push_back(
            irGenerator->generateFor(
                argument,
                i,
                scope,
                irContext,
                std::make_shared<IROperation>(IR_FUNCTION_ARGUMENT_OP),
                node->getInvocableTypeSignature()
            )
        );
    }

    auto irExpression = std::dynamic_pointer_cast<IRArrayAccessExpressionNode>(irGenerator->generateFor(node->getArrayAccess(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP)));
    auto irFunctionType = std::dynamic_pointer_cast<IRInvocableType>(irExpression->getIRType());
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto argList = irGenerator->generateArgumentPlaceholderList(irFunctionType, &arguments);
    auto callInstruction = llvm::CallInst::Create(irFunctionType->getFunctionType(), irExpression->getValue(), argList);
    return std::make_shared<IRArrayAccessInvocationExpressionNode>(node, irExpression, callInstruction, irFunctionType, arguments, irReturnType);
}