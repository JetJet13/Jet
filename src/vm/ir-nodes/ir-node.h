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
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_NODE_H
#define JETLANG_IR_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/IRBuilder.h>
#include <string>
#include "types/ir-node-type.h"

class IRNode {
public:
    bool is(IRNodeType irNodeType);
    bool isOneOf(std::vector<IRNodeType> irNodeTypes);
    virtual bool isDeclaration();
    virtual bool isExpression();
    virtual bool isTypeDeclaration();
    virtual bool isStatement();
    virtual IRNodeType getNodeType() = 0;
    virtual std::string toString() = 0;
    virtual void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) = 0;
};

#endif //JETLANG_IR_NODE_H
