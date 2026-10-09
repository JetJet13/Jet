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
// Created by Johny Georges on 2026-05-16.
//

#ifndef JETLANG_INT_MULTIPLY_OVERFLOW_IR_FUNCTION_H
#define JETLANG_INT_MULTIPLY_OVERFLOW_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class IntMultiplyOverflowIRFunction {
public:
    static std::string getIntMultiplyOverflowIRFunctionName();
    static void generateIntMultiplyOverflowFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_INT_MULTIPLY_OVERFLOW_IR_FUNCTION_H
