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
// Created by Johny Georges on 2025-11-24.
//

#ifndef JETLANG_FREE_VARIABLES_IR_INJECTOR_HELPER_H
#define JETLANG_FREE_VARIABLES_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-dref-expression-node.h"
#include "../../../../ir-nodes/ir-function-nodes/ir-function-parameter-list-node.h"

class FreeIRInjectorHelper {
public:
    static void freeNodes(std::shared_ptr<IRBlockNode> irBlockNode, std::vector<std::shared_ptr<IRNodeToFree>>* nodesToFree, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    static void freeForInLoopSource(std::shared_ptr<IRBlockNode> forInEndBlock, std::shared_ptr<IRBlockNode> forInSetupBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    static void freeNestedBlockNodes(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    static void freeVariable(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<IRVariableDeclarationNode> variableToFree, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    static void freeExpression(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<IRExpressionNode> expressionToFree, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    static void freeFunctionBlockNodes(std::shared_ptr<IRBlockNode> functionBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    static void freeFunctionParameters(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<IRFunctionParameterListNode> functionParameterList, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_FREE_VARIABLES_IR_INJECTOR_HELPER_H
