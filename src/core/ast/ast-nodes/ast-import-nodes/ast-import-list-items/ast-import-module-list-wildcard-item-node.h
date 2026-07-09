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
    std::shared_ptr<Lexeme> _lexeme;
public:
    explicit ASTImportModuleListWildcardItemNode(std::shared_ptr<Lexeme> lexeme);
    std::shared_ptr<Lexeme> getLexeme();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_WILDCARD_ITEM_NODE_H
