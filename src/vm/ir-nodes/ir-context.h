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
// Created by Johny Georges on 2025-01-13.
//

#ifndef JETLANG_IR_CONTEXT_H
#define JETLANG_IR_CONTEXT_H

#include "llvm/IR/LLVMContext.h"
#include "ir-block-nodes/ir-block-node.h"
#include "ir-module-node.h"
#include "../ir-scope/ir-scope.h"

class IRContext {
private:
    std::unique_ptr<llvm::LLVMContext>* _context;
    std::shared_ptr<IRBlockNode> _irBlock;
    std::shared_ptr<IRModuleNode> _irModule;
    IRScope _irScope;
    llvm::DataLayout* _dataLayout;
public:
    IRContext(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRModuleNode> irModule, std::unique_ptr<llvm::LLVMContext>* context);
    llvm::DataLayout* getDataLayout();
    std::unique_ptr<llvm::LLVMContext>* getContext();
    std::shared_ptr<IRBlockNode> getIRBlock();
    std::shared_ptr<IRModuleNode> getIRModule();
    IRScope* getIRScope();
    llvm::Module* getModule();
    llvm::Function* getFunction();
    bool isTargetX86_64();
    bool isTargetArm64();
    std::shared_ptr<IRContext> clone(std::shared_ptr<IRBlockNode> irBlock);
};

#endif //JETLANG_IR_CONTEXT_H
