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
// Created by Johny Georges on 2024-12-05.
//

#ifndef JETLANG_IR_CLASS_DECLARATION_NODE_H
#define JETLANG_IR_CLASS_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "ir-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"
#include "../../ir-type/ir-class-type.h"
#include "../ir-class-nodes/ir-class-constructor-node.h"
#include "../ir-class-nodes/ir-class-method-node.h"
#include "../ir-class-nodes/ir-class-pre-constructor-node.h"
#include "../ir-class-nodes/ir-class-static-property-node.h"

class IRClassDeclarationNode : public IRDeclarationNode {
private:
    std::shared_ptr<ASTClassDeclarationNode> _node;
    std::shared_ptr<IRInstructionNode> _irValue;
    std::shared_ptr<IRClassType> _type;
    std::optional<std::shared_ptr<IRClassPreConstructorNode>> _preConstructor;
    std::vector<std::shared_ptr<IRClassConstructorNode>> _constructors;
    std::vector<std::shared_ptr<IRClassMethodNode>> _methods;
    std::vector<std::shared_ptr<IRClassMethodNode>> _staticMethods;
    std::vector<std::shared_ptr<IRClassStaticPropertyNode>> _staticProperties;
public:
    IRClassDeclarationNode(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<IRInstructionNode> irValue, std::shared_ptr<IRClassType> type, std::optional<std::shared_ptr<IRClassPreConstructorNode>> preConstructor, std::vector<std::shared_ptr<IRClassConstructorNode>> constructors, std::vector<std::shared_ptr<IRClassMethodNode>> methods, std::vector<std::shared_ptr<IRClassMethodNode>> staticMethods, std::vector<std::shared_ptr<IRClassStaticPropertyNode>> staticProperties);
    std::shared_ptr<IRClassType> getIRType();
    std::optional<std::shared_ptr<IRClassPreConstructorNode>> getPreConstructor();
    std::vector<std::shared_ptr<IRClassConstructorNode>>* getConstructors();
    std::vector<std::shared_ptr<IRClassMethodNode>>* getMethods();
    std::vector<std::shared_ptr<IRClassMethodNode>>* getStaticMethods();
    std::vector<std::shared_ptr<IRClassStaticPropertyNode>>* getStaticProperties();
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CLASS_DECLARATION_NODE_H
