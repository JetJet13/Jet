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
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/IR/Constants.h>
#include <llvm/ADT/ArrayRef.h>
#include "string-literal-ir-strategy.h"

std::shared_ptr<IRStringLiteralNode> StringLiteralIRStrategy::generate(std::shared_ptr<ASTStringLiteralNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext) {
    auto chars = std::vector<llvm::Constant*>();

    for (auto character : node->getValue()) {
        chars.push_back(irGenerator->generateChar(character));
    }
    chars.push_back(irGenerator->generateChar('\0'));
    auto charIrType = irGenerator->generateIRCharType();
    auto stringArrayType = irGenerator->generateIRArrayType(charIrType, chars.size());
    auto stringArray = llvm::ConstantArray::get(
            stringArrayType->getType(),
            llvm::ArrayRef(chars)
    );

    return std::make_shared<IRStringLiteralNode>(
        node,
        stringArray,
        stringArrayType
    );
}

llvm::Constant* StringLiteralIRStrategy::generateIRString(std::string rawString, std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context) {
    auto chars = std::vector<llvm::Constant*>();
    for (auto character : rawString) {
        chars.push_back(irGenerator->generateChar(character));
    }
    chars.push_back(irGenerator->generateChar('\0'));
    auto charIrType = irGenerator->generateIRCharType();
    auto stringArrayType = irGenerator->generateIRArrayType(charIrType, chars.size());
    return llvm::ConstantArray::get(
            stringArrayType->getType(),
            llvm::ArrayRef(chars)
    );
}