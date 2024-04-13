//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_MODULE_DECLARATION_NODE_H
#define JETLANG_AST_MODULE_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-enum-nodes/ast-enum-name-node.h"
#include "../ast-enum-nodes/ast-enum-key-value-list-node.h"
#include "../ast-module-nodes/ast-module-name-node.h"

class ASTModuleDeclarationNode : public ASTNode {
private:
    ASTModuleNameNode* _name;
    ASTModuleListNode* _items;
public:
    explicit ASTModuleDeclarationNode(ASTModuleNameNode* name, ASTModuleListNode* items);
    ASTModuleListNode* getItems();
    ASTModuleNameNode* getName();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_MODULE_DECLARATION_NODE_H
