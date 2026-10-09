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

#include "ast-node-id-assignor.h"
#include "ast-node-id-strategies/variable-declaration-id-strategy/variable-declaration-id-strategy.h"
#include "ast-node-id-strategies/class-declaration-id-strategy/class-declaration-id-strategy.h"
#include "ast-node-id-strategies/enum-declaration-id-strategy/enum-declaration-id-strategy.h"
#include "ast-node-id-strategies/function-declaration-id-strategy/function-declaration-id-strategy.h"
#include "ast-node-id-strategies/procedure-declaration-id-strategy/procedure-declaration-id-strategy.h"
#include "ast-node-id-strategies/module-declaration-id-strategy/module-declaration-id-strategy.h"
#include "ast-node-id-strategies/import-single-module-declaration-id-strategy/import-single-module-declaration-id-strategy.h"
#include "ast-node-id-strategies/use-single-module-declaration-id-strategy/use-single-module-declaration-id-strategy.h"
#include "ast-node-id-strategies/import-many-module-declaration-id-strategy/import-many-module-declaration-id-strategy.h"
#include "ast-node-id-strategies/use-many-module-declaration-id-strategy/use-many-module-declaration-id-strategy.h"
#include "ast-node-id-strategies/identifier-id-strategy/identifier-id-strategy.h"
#include "ast-node-id-strategies/identifier-expression-id-strategy/identifier-expression-id-strategy.h"
#include "ast-node-id-strategies/import-many-by-wildcard-module-declaration-id-strategy/import-many-by-wildcard-module-declaration-id-strategy.h"
#include "ast-node-id-strategies/use-many-by-wildcard-module-declaration-id-strategy/use-many-by-wildcard-module-declaration-id-strategy.h"
#include "ast-node-id-strategies/module-access-expression-id-strategy/module-access-expression-id-strategy.h"
#include "ast-node-id-strategies/interface-type-declaration-id-strategy/interface-type-declaration-id-strategy.h"
#include "ast-node-id-strategies/custom-type-declaration-id-strategy/custom-type-declaration-id-strategy.h"

ASTNodeIdAssignor::ASTNodeIdAssignor(std::shared_ptr<TokenTable> tokenTable) {
    _tokenTable = tokenTable;
    _strategies = std::unordered_map<ASTNodeType, std::shared_ptr<ASTNodeIdStrategy>, std::hash<int>>();
    this->initStrategies();
}

void ASTNodeIdAssignor::initStrategies() {
    this->addStrategy(AST_IDENTIFIER_NODE, std::make_shared<IdentifierIdStrategy>(_tokenTable));
    this->addStrategy(AST_IDENTIFIER_EXPRESSION_NODE, std::make_shared<IdentifierExpressionIdStrategy>(_tokenTable));
    this->addStrategy(AST_CALLABLE_IDENTIFIER_EXPRESSION_NODE, std::make_shared<IdentifierExpressionIdStrategy>(_tokenTable));
    this->addStrategy(AST_VARIABLE_DECLARATION_NODE, std::make_shared<VariableDeclarationIdStrategy>(_tokenTable));
    this->addStrategy(AST_CLASS_DECLARATION_NODE, std::make_shared<ClassDeclarationIdStrategy>(_tokenTable));
    this->addStrategy(AST_ENUM_DECLARATION_NODE, std::make_shared<EnumDeclarationIdStrategy>(_tokenTable));
    this->addStrategy(AST_FUNCTION_DECLARATION_NODE, std::make_shared<FunctionDeclarationIdStrategy>(_tokenTable));
    this->addStrategy(AST_PROCEDURE_DECLARATION_NODE, std::make_shared<ProcedureDeclarationIdStrategy>(_tokenTable));
    this->addStrategy(AST_MODULE_DECLARATION_NODE, std::make_shared<ModuleDeclarationIdStrategy>(_tokenTable));
    this->addStrategy(AST_MODULE_ACCESS_EXPRESSION_NODE, std::make_shared<ModuleAccessExpressionIdStrategy>(_tokenTable));
    this->addStrategy(AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE, std::make_shared<ImportSingleModuleDeclarationIdStrategy>(_tokenTable));
    this->addStrategy(AST_USE_SINGLE_MODULE_DECLARATION_NODE, std::make_shared<UseSingleModuleDeclarationIdStrategy>(_tokenTable));
    this->addStrategy(AST_IMPORT_MANY_MODULE_DECLARATION_NODE, std::make_shared<ImportManyModuleDeclarationIdStrategy>(_tokenTable));
    this->addStrategy(AST_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE, std::make_shared<ImportManyByWildcardModuleDeclarationIdStrategy>(_tokenTable));
    this->addStrategy(AST_USE_MANY_MODULE_DECLARATION_NODE, std::make_shared<UseManyModuleDeclarationIdStrategy>(_tokenTable));
    this->addStrategy(AST_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE, std::make_shared<UseManyByWildcardModuleDeclarationIdStrategy>(_tokenTable));
    this->addStrategy(AST_INTERFACE_TYPE_DECLARATION_NODE, std::make_shared<InterfaceTypeDeclarationIdStrategy>(_tokenTable));
    this->addStrategy(AST_CUSTOM_TYPE_DECLARATION_NODE, std::make_shared<CustomTypeDeclarationIdStrategy>(_tokenTable));
}

void ASTNodeIdAssignor::addStrategy(ASTNodeType astNodeType, std::shared_ptr<ASTNodeIdStrategy> declarationIdStrategy) {
    _strategies.insert(std::pair(astNodeType, declarationIdStrategy));
}

void ASTNodeIdAssignor::assignIdIfNecessary(std::shared_ptr<ASTNode> node) {
    auto reducerStrategy = _strategies.find(node->getNodeType());
    if (reducerStrategy != _strategies.end()) {
        reducerStrategy->second->assign(node);
    }
}