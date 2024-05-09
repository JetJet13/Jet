//
// Created by Johny Georges on 2024-05-02.
//

#include "declaration-id-assignor.h"
#include "declaration-id-strategies/variable-declaration-id-strategy/variable-declaration-id-strategy.h"
#include "declaration-id-strategies/class-declaration-id-strategy/class-declaration-id-strategy.h"
#include "declaration-id-strategies/enum-declaration-id-strategy/enum-declaration-id-strategy.h"
#include "declaration-id-strategies/function-declaration-id-strategy/function-declaration-id-strategy.h"
#include "declaration-id-strategies/procedure-declaration-id-strategy/procedure-declaration-id-strategy.h"
#include "declaration-id-strategies/module-declaration-id-strategy/module-declaration-id-strategy.h"
#include "declaration-id-strategies/import-single-module-declaration-id-strategy/import-single-module-declaration-id-strategy.h"
#include "declaration-id-strategies/use-single-module-declaration-id-strategy/use-single-module-declaration-id-strategy.h"
#include "declaration-id-strategies/import-many-module-declaration-id-strategy/import-many-module-declaration-id-strategy.h"
#include "declaration-id-strategies/use-many-module-declaration-id-strategy/use-many-module-declaration-id-strategy.h"

DeclarationIdAssignor::DeclarationIdAssignor(TokenTable* tokenTable) {
    _tokenTable = tokenTable;
    _strategies = std::unordered_map<ASTNodeType, DeclarationIdStrategy*, std::hash<int>>();
    this->initStrategies();
}

void DeclarationIdAssignor::initStrategies() {
    this->addStrategy(AST_VARIABLE_DECLARATION_NODE, new VariableDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_CLASS_DECLARATION_NODE, new ClassDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_ENUM_DECLARATION_NODE, new EnumDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_FUNCTION_DECLARATION_NODE, new FunctionDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_PROCEDURE_DECLARATION_NODE, new ProcedureDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_MODULE_DECLARATION_NODE, new ModuleDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE, new ImportSingleModuleDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_USE_SINGLE_MODULE_DECLARATION_NODE, new UseSingleModuleDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_IMPORT_MANY_MODULE_DECLARATION_NODE, new ImportManyModuleDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_USE_MANY_MODULE_DECLARATION_NODE, new UseManyModuleDeclarationIdStrategy(_tokenTable));
}

void DeclarationIdAssignor::addStrategy(ASTNodeType astNodeType, DeclarationIdStrategy* declarationIdStrategy) {
    _strategies.insert(std::pair(astNodeType, declarationIdStrategy));
}

void DeclarationIdAssignor::assignId(ASTNode* node) {
    auto reducerStrategy = _strategies.find(node->getNodeType());
    if (reducerStrategy == _strategies.end()) {
        throw std::invalid_argument("unable to determine declaration id generator for node");
    }
    reducerStrategy->second->assign(node);
}