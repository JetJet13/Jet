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
// Created by Johny Georges on 2026-03-14.
//

#ifndef JETLANG_IR_CLASS_STATIC_PROPERTY_NODE_H
#define JETLANG_IR_CLASS_STATIC_PROPERTY_NODE_H

#include <llvm/IR/GlobalVariable.h>
#include "../ir-expression-nodes/ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-property-declaration-node.h"

class IRClassStaticPropertyNode {
private:
    std::shared_ptr<ASTClassPropertyDeclarationNode> _node;
    llvm::GlobalVariable* _irValue;
    std::shared_ptr<IRExpressionNode> _initialIRValue;
    std::shared_ptr<IRType> _irType;
public:
    IRClassStaticPropertyNode(std::shared_ptr<ASTClassPropertyDeclarationNode> node, llvm::GlobalVariable* irValue, std::shared_ptr<IRExpressionNode> initialIRValue, std::shared_ptr<IRType> irType);
    llvm::GlobalVariable* getGlobalVariable();
    std::shared_ptr<IRExpressionNode> getInitialIRValue();
    std::shared_ptr<IRType> getIRType();
};

#endif //JETLANG_IR_CLASS_STATIC_PROPERTY_NODE_H
