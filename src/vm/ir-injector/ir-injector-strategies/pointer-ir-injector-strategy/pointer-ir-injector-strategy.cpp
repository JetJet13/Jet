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

#include "pointer-ir-injector-strategy.h"

llvm::Value* PointerIRInjectorStrategy::inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
   if (irExpression->is(IR_SHARE_EXPRESSION_NODE)) {
        return this->_pointerIRShareExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRShareExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    }else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_pointerIRIdentifierExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRIdentifierExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    }
    throw std::logic_error("PointerIRInjectorStrategy - invalid ir expression with pointer type");
}