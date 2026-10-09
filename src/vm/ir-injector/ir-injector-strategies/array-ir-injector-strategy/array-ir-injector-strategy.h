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
// Created by Johny Georges on 2024-08-13.
//

#ifndef JETLANG_ARRAY_IR_INJECTOR_STRATEGY_H
#define JETLANG_ARRAY_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-array-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-aggregate-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-array-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-tuple-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "strategies/array-ir-array-expression-injector-strategy/array-ir-array-expression-injector-strategy.h"
#include "strategies/array-ir-object-access-expression-injector-strategy/array-ir-object-access-expression-injector-strategy.h"
#include "strategies/array-ir-array-access-expression-injector-strategy/array-ir-array-access-expression-injector-strategy.h"
#include "strategies/array-ir-tuple-access-expression-injector-strategy/array-ir-tuple-access-expression-injector-strategy.h"
#include "strategies/array-ir-dref-expression-injector-strategy/array-ir-dref-expression-injector-strategy.h"
#include "strategies/array-ir-identifier-expression-injector-strategy/array-ir-identifier-expression-injector-strategy.h"
#include "strategies/array-ir-concat-expression-injector-strategy/array-ir-concat-expression-injector-strategy.h"

class ArrayIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    ArrayIRArrayExpressionInjectorStrategy _arrayIRArrayExpressionInjectorStrategy = ArrayIRArrayExpressionInjectorStrategy();
    ArrayIRObjectAccessExpressionInjectorStrategy _arrayIRObjectAccessExpressionInjectorStrategy = ArrayIRObjectAccessExpressionInjectorStrategy();
    ArrayIRArrayAccessExpressionInjectorStrategy _arrayIRArrayAccessExpressionInjectorStrategy = ArrayIRArrayAccessExpressionInjectorStrategy();
    ArrayIRTupleAccessExpressionInjectorStrategy _arrayIRTupleAccessExpressionInjectorStrategy = ArrayIRTupleAccessExpressionInjectorStrategy();
    ArrayIRDrefExpressionInjectorStrategy _arrayIRDrefExpressionInjectorStrategy = ArrayIRDrefExpressionInjectorStrategy();
    ArrayIRIdentifierExpressionInjectorStrategy _arrayIRIdentifierExpressionInjectorStrategy = ArrayIRIdentifierExpressionInjectorStrategy();
    ArrayIRConcatExpressionInjectorStrategy _arrayIRConcatExpressionInjectorStrategy = ArrayIRConcatExpressionInjectorStrategy();
public:
    llvm::Value* inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) override;
};

#endif //JETLANG_ARRAY_IR_INJECTOR_STRATEGY_H
