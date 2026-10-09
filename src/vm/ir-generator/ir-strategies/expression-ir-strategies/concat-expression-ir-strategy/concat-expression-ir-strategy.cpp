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
// Created by Johny Georges on 2025-06-09.
//

#include "concat-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRConcatExpressionNode> ConcatExpressionIRStrategy::generate(std::shared_ptr<ASTConcatExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope, irContext, irOperation);
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope, irContext, irOperation);
    auto irType = std::dynamic_pointer_cast<IRArrayPointerType>(irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext));
    auto function = node->getTypeSignature()->typeTargetIs(STRING_LITERAL_TYPE_SOURCE)
            ? irContext->getIRModule()->getStringConcatFunction()
            : irContext->getIRModule()->getArrayConcatFunction();
    auto args = std::vector({ leftExpressionIr, rightExpressionIr });
    auto placeholderArgs = node->getTypeSignature()->typeTargetIs(STRING_LITERAL_TYPE_SOURCE)
            ? std::vector<llvm::Value*>({
                irGenerator->generateConstantPointer(),
                irGenerator->generateConstantPointer()
              })
            : std::vector<llvm::Value*>({
                irGenerator->generateConstantPointer(),
                irGenerator->generateConstantPointer(),
                irGenerator->generatePlaceholderTypeValueArgument()
              });
    auto concatCall = llvm::CallInst::Create(
            function,
            placeholderArgs
    );
    return std::make_shared<IRConcatExpressionNode>(
            node,
            concatCall,
            leftExpressionIr,
            rightExpressionIr,
            irType
    );
}