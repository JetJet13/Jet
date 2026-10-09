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
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_CLASS_DECLARATION_ID_STRATEGY_H
#define JETLANG_CLASS_DECLARATION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ast-node-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-property-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-method-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-constructor-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-method-call-node.h"

class ClassDeclarationIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
private:
    std::string generateClassPropertyId(std::string className, std::shared_ptr<ASTClassPropertyNameNode> classPropertyName);
    std::string generateClassMethodId(std::string className, std::shared_ptr<ASTClassMethodNameNode> classMethodName);
    std::string generateClassMethodId(std::string className, std::shared_ptr<ASTClassMethodCallNode> classMethodCall);
    std::string generateClassMethodId(std::string className, std::shared_ptr<Lexeme> lexeme);
    std::string generateClassConstructorDeclarationId(std::string className, uint64_t constructorIndex, std::shared_ptr<ASTClassConstructorDeclarationNode> constructorDeclaration);
public:
    void assign(std::shared_ptr<ASTNode> node) override;
};

#endif //JETLANG_CLASS_DECLARATION_ID_STRATEGY_H
