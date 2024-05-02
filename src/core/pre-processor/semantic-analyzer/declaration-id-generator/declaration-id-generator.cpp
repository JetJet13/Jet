//
// Created by Johny Georges on 2024-05-02.
//

#include "declaration-id-generator.h"
#include "declaration-id-strategies/variable-declaration-id-strategy/variable-declaration-id-strategy.h"

DeclarationIdGenerator::DeclarationIdGenerator(TokenTable* tokenTable) {
    _tokenTable = tokenTable;
    _strategies = std::unordered_map<ASTNodeType, DeclarationIdStrategy*, std::hash<int>>();
    this->initStrategies();
}

void DeclarationIdGenerator::initStrategies() {
    this->addStrategy(AST_VARIABLE_DECLARATION_NODE, new VariableDeclarationIdStrategy(_tokenTable));
}

void DeclarationIdGenerator::addStrategy(ASTNodeType astNodeType, DeclarationIdStrategy* declarationIdStrategy) {
    _strategies.insert(std::pair(astNodeType, declarationIdStrategy));
}

DeclarationId* DeclarationIdGenerator::generate(ASTNode* node) {
    auto reducerStrategy = _strategies.find(node->getNodeType());
    if (reducerStrategy == _strategies.end()) {
        throw std::invalid_argument("unable to determine declaration id generator for node");
    }
    return reducerStrategy->second->generate(node);
}