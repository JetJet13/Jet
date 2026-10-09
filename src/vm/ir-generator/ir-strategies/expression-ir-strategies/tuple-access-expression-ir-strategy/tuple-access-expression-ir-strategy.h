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
// Created by Johny Georges on 2024-10-09.
//

#ifndef JETLANG_TUPLE_ACCESS_EXPRESSION_IR_STRATEGY_H
#define JETLANG_TUPLE_ACCESS_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-tuple-access-expression-node.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"

class TupleAccessExpressionIRStrategy {
public:
    std::shared_ptr<IRTupleAccessExpressionNode> generate(std::shared_ptr<ASTTupleAccessExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_TUPLE_ACCESS_EXPRESSION_IR_STRATEGY_H
