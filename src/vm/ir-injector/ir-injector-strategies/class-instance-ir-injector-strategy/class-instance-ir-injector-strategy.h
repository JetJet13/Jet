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
// Created by Johny Georges on 2025-12-26.
//

#ifndef JETLANG_CLASS_INSTANCE_IR_INJECTOR_STRATEGY_H
#define JETLANG_CLASS_INSTANCE_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"
#include "strategies/class-instance-ir-object-access-expression-injector-strategy/class-instance-ir-object-access-expression-injector-strategy.h"
#include "strategies/class-instance-ir-tuple-access-expression-injector-strategy/class-instance-ir-tuple-access-expression-injector-strategy.h"
#include "strategies/class-instance-ir-array-access-expression-injector-strategy/class-instance-ir-array-access-expression-injector-strategy.h"
#include "strategies/class-instance-ir-dref-expression-injector-strategy/class-instance-ir-dref-expression-injector-strategy.h"
#include "strategies/class-instance-ir-this-expression-injector-strategy/class-instance-ir-this-expression-injector-strategy.h"


class ClassInstanceIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    ClassInstanceIRObjectAccessExpressionInjectorStrategy _objectAccessExpressionInjector = ClassInstanceIRObjectAccessExpressionInjectorStrategy();
    ClassInstanceIRTupleAccessExpressionInjectorStrategy _tupleAccessExpressionInjector = ClassInstanceIRTupleAccessExpressionInjectorStrategy();
    ClassInstanceIRArrayAccessExpressionInjectorStrategy _arrayAccessExpressionInjector = ClassInstanceIRArrayAccessExpressionInjectorStrategy();
    ClassInstanceIRDrefExpressionInjectorStrategy _drefExpressionInjector = ClassInstanceIRDrefExpressionInjectorStrategy();
    ClassInstanceIRThisExpressionInjectorStrategy _thisExpressionInjector = ClassInstanceIRThisExpressionInjectorStrategy();
public:
    llvm::Value* inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) override;
    llvm::Value* inject(std::shared_ptr<IRIdentifierExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_CLASS_INSTANCE_IR_INJECTOR_STRATEGY_H
