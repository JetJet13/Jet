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
// Created by Johny Georges on 2025-12-19.
//

#ifndef JETLANG_OBJECT_ACCESS_IR_INJECTOR_HELPER_H
#define JETLANG_OBJECT_ACCESS_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-tuple-access-expression-node.h"

class ObjectAccessIRInjectorHelper {
public:
    static llvm::Value* getPointerToTarget(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRObjectAccessExpressionNode> irExpression, llvm::Value* sourceValue);
    static llvm::Value* getPointerToTarget(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRTupleAccessExpressionNode> irExpression, llvm::Value* sourceValue);
};

#endif //JETLANG_OBJECT_ACCESS_IR_INJECTOR_HELPER_H
