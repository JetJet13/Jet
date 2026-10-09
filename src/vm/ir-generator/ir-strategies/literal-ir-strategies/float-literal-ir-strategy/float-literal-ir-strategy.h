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
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_FLOAT_LITERAL_IR_STRATEGY_H
#define JETLANG_FLOAT_LITERAL_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "../../../../../core/ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../../../../core/ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"
#include "../../../../ir-nodes/ir-literal-nodes/ir-float-literal-node.h"
#include "../../../../ir-nodes/ir-module-node.h"
#include "../../../../ir-nodes/ir-context.h"
#include "../../../ir-generator.h"

class FloatLiteralIRStrategy {
public:
    std::shared_ptr<IRFloatLiteralNode> generate(std::shared_ptr<ASTFloatLiteralNode> node, std::shared_ptr<IRGenerator> irGenerator,  std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_FLOAT_LITERAL_IR_STRATEGY_H
