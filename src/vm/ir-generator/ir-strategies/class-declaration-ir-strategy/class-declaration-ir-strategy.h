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
// Created by Johny Georges on 2024-12-09.
//

#ifndef JETLANG_CLASS_DECLARATION_IR_STRATEGY_H
#define JETLANG_CLASS_DECLARATION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-class-declaration-node.h"
#include "../../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"

class ClassDeclarationIRStrategy {
private:
    std::optional<std::shared_ptr<IRClassPreConstructorNode>> generatePreConstructor(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    std::shared_ptr<IRClassConstructorNode> generate(std::shared_ptr<ASTClassConstructorDeclarationNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    std::shared_ptr<IRClassMethodNode> generate(std::shared_ptr<ASTClassMethodDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    std::shared_ptr<IRClassMethodNode> generateStatic(std::shared_ptr<ASTClassMethodDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    std::shared_ptr<IRClassStaticPropertyNode> generateStaticProperty(std::shared_ptr<ASTClassPropertyDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    void declareMethod(std::shared_ptr<ASTClassMethodDeclarationNode> node, bool isExportable, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    void declareStaticMethod(std::shared_ptr<ASTClassMethodDeclarationNode> node, bool isExportable, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    void declareConstructor(std::shared_ptr<ASTClassConstructorDeclarationNode> node, bool isExportable, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    void declareStaticProperty(std::shared_ptr<ASTClassPropertyDeclarationNode> node, bool isExportable, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
public:
    std::shared_ptr<IRClassDeclarationNode> generate(std::shared_ptr<ASTClassDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};


#endif //JETLANG_CLASS_DECLARATION_IR_STRATEGY_H
