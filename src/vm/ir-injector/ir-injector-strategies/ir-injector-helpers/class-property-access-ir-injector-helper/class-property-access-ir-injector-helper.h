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
// Created by Johny Georges on 2025-01-02.
//

#ifndef JETLANG_CLASS_PROPERTY_ACCESS_IR_INJECTOR_HELPER_H
#define JETLANG_CLASS_PROPERTY_ACCESS_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-static-property-access-expression-node.h"

class ClassPropertyAccessIRInjectorHelper {
public:
    static llvm::Value* inject(std::shared_ptr<IRClassPropertyAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation);
    static llvm::Value* inject(std::shared_ptr<IRClassStaticPropertyAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_CLASS_PROPERTY_ACCESS_IR_INJECTOR_HELPER_H
