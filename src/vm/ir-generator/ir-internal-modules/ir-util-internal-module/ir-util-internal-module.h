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
// Created by Johny Georges on 2024-10-21.
//

#ifndef JETLANG_IR_UTIL_INTERNAL_MODULE_H
#define JETLANG_IR_UTIL_INTERNAL_MODULE_H

#include <memory>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-module-node.h"

class IRUtilInternalModule {
public:
    static void augment(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> coreIrModule);
    static std::string getIRName(std::string id, uint64_t numArgs);
};

#endif //JETLANG_IR_UTIL_INTERNAL_MODULE_H
