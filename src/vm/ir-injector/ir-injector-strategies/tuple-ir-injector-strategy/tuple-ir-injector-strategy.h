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
// Created by Johny Georges on 2024-08-15.
//

#ifndef JETLANG_TUPLE_IR_INJECTOR_STRATEGY_H
#define JETLANG_TUPLE_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-tuple-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-tuple-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "strategies/tuple-ir-tuple-expression-injector-strategy/tuple-ir-tuple-expression-injector-strategy.h"
#include "strategies/tuple-ir-identifier-expression-injector-strategy/tuple-ir-identifier-expression-injector-strategy.h"
#include "strategies/tuple-ir-tuple-access-expression-injector-strategy/tuple-ir-tuple-access-expression-injector-strategy.h"
#include "strategies/tuple-ir-class-property-access-expression-injector-strategy/tuple-ir-class-property-access-expression-injector-strategy.h"
#include "strategies/tuple-ir-object-access-expression-injector-strategy/tuple-ir-object-access-expression-injector-strategy.h"
#include "strategies/tuple-ir-array-access-expression-injector-strategy/tuple-ir-array-access-expression-injector-strategy.h"
#include "strategies/tuple-ir-dref-expression-injector-strategy/tuple-ir-dref-expression-injector-strategy.h"

class TupleIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    TupleIRTupleExpressionInjectorStrategy _tupleIRTupleExpressionInjectorStrategy = TupleIRTupleExpressionInjectorStrategy();
    TupleIRDrefExpressionInjectorStrategy _tupleIRDrefExpressionInjectorStrategy = TupleIRDrefExpressionInjectorStrategy();
    TupleIRIdentifierExpressionInjectorStrategy _tupleIRIdentifierExpressionInjectorStrategy = TupleIRIdentifierExpressionInjectorStrategy();
    TupleIRArrayAccessExpressionInjectorStrategy _tupleIRArrayAccessExpressionInjectorStrategy = TupleIRArrayAccessExpressionInjectorStrategy();
    TupleIRObjectAccessExpressionInjectorStrategy _tupleIRObjectAccessExpressionInjectorStrategy = TupleIRObjectAccessExpressionInjectorStrategy();
    TupleIRTupleAccessExpressionInjectorStrategy _tupleIRTupleAccessExpressionInjectorStrategy = TupleIRTupleAccessExpressionInjectorStrategy();
    TupleIRClassPropertyAccessExpressionInjectorStrategy _tupleIRClassPropertyAccessExpressionInjectorStrategy = TupleIRClassPropertyAccessExpressionInjectorStrategy();
public:
    llvm::Value* inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) override;
};

#endif //JETLANG_TUPLE_IR_INJECTOR_STRATEGY_H
