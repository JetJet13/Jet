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

ASTNodeIdAssignor::ASTNodeIdAssignor(TokenTable* tokenTable) {
    _tokenTable = tokenTable;
    _strategies = std::unordered_map<ASTNodeType, ASTNodeIdStrategy*, std::hash<int>>();
    this->initStrategies();
}

void ASTNodeIdAssignor::initStrategies() {
    this->addStrategy(AST_IDENTIFIER_NODE, new IdentifierIdStrategy(_tokenTable));
    this->addStrategy(AST_IDENTIFIER_EXPRESSION_NODE, new IdentifierExpressionIdStrategy(_tokenTable));
    this->addStrategy(AST_CALLABLE_IDENTIFIER_EXPRESSION_NODE, new IdentifierExpressionIdStrategy(_tokenTable));
    this->addStrategy(AST_VARIABLE_DECLARATION_NODE, new VariableDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_CLASS_DECLARATION_NODE, new ClassDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_ENUM_DECLARATION_NODE, new EnumDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_FUNCTION_DECLARATION_NODE, new FunctionDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_PROCEDURE_DECLARATION_NODE, new ProcedureDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_MODULE_DECLARATION_NODE, new ModuleDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_MODULE_ACCESS_EXPRESSION_NODE, new ModuleAccessExpressionIdStrategy(_tokenTable));
    this->addStrategy(AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE, new ImportSingleModuleDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_USE_SINGLE_MODULE_DECLARATION_NODE, new UseSingleModuleDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_IMPORT_MANY_MODULE_DECLARATION_NODE, new ImportManyModuleDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE, new ImportManyByWildcardModuleDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_USE_MANY_MODULE_DECLARATION_NODE, new UseManyModuleDeclarationIdStrategy(_tokenTable));
    this->addStrategy(AST_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE, new UseManyByWildcardModuleDeclarationIdStrategy(_tokenTable));
}

void ASTNodeIdAssignor::addStrategy(ASTNodeType astNodeType, ASTNodeIdStrategy* declarationIdStrategy) {
    _strategies.insert(std::pair(astNodeType, declarationIdStrategy));
}

void ASTNodeIdAssignor::assignIdIfNecessary(ASTNode* node) {
    auto reducerStrategy = _strategies.find(node->getNodeType());
    if (reducerStrategy != _strategies.end()) {
        reducerStrategy->second->assign(node);
    }
}