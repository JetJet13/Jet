//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_NODE_H
#define JETLANG_AST_IMPORT_MODULE_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-import-module-list-item-node.h"
#include "ast-import-module-list-start-node.h"
#include "ast-import-module-list-end-node.h"

class ASTImportModuleListNode : public ASTNode {
private:
    ASTImportModuleListStartNode* _importModuleListStartNode;
    ASTImportModuleListEndNode* _importModuleListEndNode;
    std::vector<ASTImportModuleListItemNode*> _items;
public:
    ASTImportModuleListNode(ASTImportModuleListStartNode* importModuleListStartNode, ASTImportModuleListEndNode* importModuleListEndNode);
    ASTImportModuleListNode(ASTImportModuleListStartNode* importModuleListStartNode, std::vector<ASTImportModuleListItemNode*> items, ASTImportModuleListEndNode* importModuleListEndNode);
    std::vector<ASTImportModuleListItemNode*> getItems();
    unsigned long numItems();
    ASTImportModuleListNode* addItem(ASTImportModuleListItemNode* item);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_NODE_H
