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
// Created by Johny Georges on 2024-11-12.
//

#ifndef JETLANG_LAMBDA_EXPRESSION_IR_STRATEGY_H
#define JETLANG_LAMBDA_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-nodes/ir-lambda-with-block-expression-node.h"
#include "../../../ir-generator.h"
#include "../../../../ir-nodes/ir-module-node.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-nodes/ir-lambda-with-fat-arrow-expression-node.h"

class LambdaExpressionIRStrategy {
private:
    void setupParameters(std::shared_ptr<LambdaExpressionTypeSignature> typeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, llvm::Function* irFunction, std::shared_ptr<IRFunctionParameterListNode> functionParameterList, std::shared_ptr<IRBlockNode> functionBlock, std::shared_ptr<IRContext> irContext);
    llvm::Function* generateLambdaCleanupFunction(std::shared_ptr<IRLambdaType> irLambdaType, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext);
public:
    std::shared_ptr<IRLambdaWithBlockExpressionNode> generate(std::shared_ptr<ASTLambdaExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
    std::shared_ptr<IRLambdaWithFatArrowExpressionNode> generate(std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_LAMBDA_EXPRESSION_IR_STRATEGY_H
