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
// Created by Johny Georges on 2025-12-13.
//

#ifndef JETLANG_DEBUG_IR_INJECTOR_HELPER_H
#define JETLANG_DEBUG_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-dref-expression-node.h"
#include "../../../../ir-nodes/ir-function-nodes/ir-function-parameter-list-node.h"

class DebugIRInjectorHelper {
private:
    static inline bool _debugMode = false;
public:
    static void enable();
    static void disable();
    static void injectFunctionEnterLog(std::shared_ptr<IRBlockNode> irBlockNode, std::string functionName, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    static void injectFunctionExitLog(std::shared_ptr<IRBlockNode> irBlockNode, std::string functionName, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    static void injectControlFlowEnterLog(std::shared_ptr<IRBlockNode> irBlockNode, int index, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    static void injectControlFlowExitLog(std::shared_ptr<IRBlockNode> irBlockNode, int index, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    static void injectRefCountLog(std::shared_ptr<IRBlockNode> irBlockNode, llvm::Value* idValue, llvm::Value* refValue, std::shared_ptr<IRModuleNode> irModule);
    static void injectLog(std::shared_ptr<IRBlockNode> irBlockNode, llvm::Value* log, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    static void injectLog(std::shared_ptr<IRBlockNode> irBlockNode, int log, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    static void injectLog(std::shared_ptr<IRBlockNode> irBlockNode, std::string log, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
};

#endif //JETLANG_DEBUG_IR_INJECTOR_HELPER_H
