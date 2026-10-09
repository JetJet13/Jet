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
// Created by Johny Georges on 2026-02-12.
//

#ifndef JETLANG_INCREMENT_REF_COUNT_IF_NECESSARY_IR_FUNCTION_H
#define JETLANG_INCREMENT_REF_COUNT_IF_NECESSARY_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

// We shouldn't need this function since calling CopyValue should take care of incrementing
// the ref count. That being said, I will leave this in just in case I discover an edge case
// where its needed.
class IncrementRefCountIfNecessaryIRFunction {
public:
    static std::string getIncrementRefCountIfNecessaryIRFunctionName();
    static void generateIncrementRefCountIfNecessaryFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_INCREMENT_REF_COUNT_IF_NECESSARY_IR_FUNCTION_H
