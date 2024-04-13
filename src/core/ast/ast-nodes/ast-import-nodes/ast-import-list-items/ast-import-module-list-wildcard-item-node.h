//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_WILDCARD_ITEM_NODE_H
#define JETLANG_AST_IMPORT_MODULE_LIST_WILDCARD_ITEM_NODE_H

#include <string>
#include "../../ast-node.h"
#include "../../ast-identifier-node.h"
#include "../ast-import-module-name-node.h"
#include "ast-import-module-list-base-item-node.h"


class ASTImportModuleListWildcardItemNode : public ASTImportModuleListBaseItemNode {
    Lexeme* _lexeme;
public:
    explicit ASTImportModuleListWildcardItemNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_WILDCARD_ITEM_NODE_H
