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
// Created by Johny Georges on 2025-03-24.
//

#ifndef JETLANG_POINTER_IR_INJECTOR_HELPER_H
#define JETLANG_POINTER_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"

class PointerIRInjectorHelper {
private:
    static std::shared_ptr<IRInstructionNode> injectPointerSourceAllocation(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRPointerType> irPointerType, llvm::Value* sourceValue, std::shared_ptr<IRModuleNode> irModule);
public:
    static llvm::Value* injectPointerCopy(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRPointerType> irPointerType, std::shared_ptr<IRInstructionNode> sourceValueAllocation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRInjector> irInjector);
    static llvm::Value* injectPointerCopy(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRPointerType> irPointerType, llvm::Value* sourcePointer, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRInjector> irInjector);
};

#endif //JETLANG_POINTER_IR_INJECTOR_HELPER_H
