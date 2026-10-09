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
// Created by Johny Georges on 2024-06-25.
//

#ifndef JETLANG_VARIABLE_DECLARATION_IR_STRATEGY_H
#define JETLANG_VARIABLE_DECLARATION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../core/ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-variable-declaration-node.h"

class VariableDeclarationIRStrategy {
private:
    std::shared_ptr<IROperation> determineOperationType(std::shared_ptr<ASTVariableDeclarationNode> node);
    std::shared_ptr<IRInstructionNode> generateVariableAllocation(std::shared_ptr<ASTVariableDeclarationNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRType> irType, std::shared_ptr<IRContext> irContext);
public:
    std::shared_ptr<IRVariableDeclarationNode> generate(std::shared_ptr<ASTVariableDeclarationNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_VARIABLE_DECLARATION_IR_STRATEGY_H
