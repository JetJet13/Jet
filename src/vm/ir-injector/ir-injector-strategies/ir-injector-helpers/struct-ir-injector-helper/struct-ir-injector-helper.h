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
// Created by Johny Georges on 2024-09-14.
//

#ifndef JETLANG_STRUCT_IR_INJECTOR_HELPER_H
#define JETLANG_STRUCT_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../../ir-nodes/ir-instruction-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../ir-injector.h"
#include "../../../../ir-type/ir-struct-ref-type.h"

class StructIRInjectorHelper {
public:
    static llvm::Value* injectStructRef(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInstructionNode> structRefAllocation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRInjector> irInjector);
    static llvm::Value* injectStructRefCopy(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRStructRefType> irStructRefType, llvm::Value* structRefSource, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRInjector> irInjector);
    static llvm::Value* injectStructRefCopy(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRStructRefType> irStructRefType, llvm::Value* structRefSource, llvm::Value* structRefDestination, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRInjector> irInjector);
};

#endif //JETLANG_STRUCT_IR_INJECTOR_HELPER_H
