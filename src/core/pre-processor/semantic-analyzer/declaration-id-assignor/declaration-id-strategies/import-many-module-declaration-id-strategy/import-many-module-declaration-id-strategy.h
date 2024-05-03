//
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_IMPORT_MANY_MODULE_DECLARATION_ID_STRATEGY_H
#define JETLANG_IMPORT_MANY_MODULE_DECLARATION_ID_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../declaration-id-strategy.h"

class ImportManyModuleDeclarationIdStrategy : public DeclarationIdStrategy {
    using DeclarationIdStrategy::DeclarationIdStrategy;
public:
    void assign(ASTNode* node) override;
};


#endif //JETLANG_IMPORT_MANY_MODULE_DECLARATION_ID_STRATEGY_H
