//
// Created by Johny Georges on 2024-06-05.
//

#ifndef JETLANG_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_ID_STRATEGY_H
#define JETLANG_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ast-node-id-strategy.h"

class ImportManyByWildcardModuleDeclarationIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
public:
    void assign(std::shared_ptr<ASTNode> node) override;
};


#endif //JETLANG_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_ID_STRATEGY_H
