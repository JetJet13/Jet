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
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-unary-negate-expression-injector-strategy.h"

llvm::Value* LiteralIRUnaryNegateExpressionInjectorStrategy::inject(std::shared_ptr<IRUnaryNegateExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto value = irInjector->inject(irBlock, irExpression->getIRExpression(), std::make_shared<IROperation>(IR_OPERAND_VALUE_OP), irModule, scope);
    if (value->getType()->isIntegerTy(1)) {
        return irBlock->getBuilder()->get()->CreateXor(value, irBlock->getBuilder()->get()->getTrue());
    }
    return irBlock->getBuilder()->get()->getFalse();
}