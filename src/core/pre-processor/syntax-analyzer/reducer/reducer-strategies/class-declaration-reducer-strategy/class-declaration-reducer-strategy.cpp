//
// Created by Johny Georges on 2024-04-20.
//

#include "class-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"

ASTNode* ClassDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() == 3) {
        return new ASTClassDeclarationNode(
                (ASTClassNode*)nodes[0],
                (ASTClassNameNode*)nodes[1],
                (ASTClassBlockNode*)nodes[2]
        );
    }

    if (nodes.size() == 4 && nodes.at(2)->is(AST_IMPLEMENTS_INTERFACE_LIST_NODE)) {
        return new ASTClassDeclarationNode(
                (ASTClassNode*)nodes[0],
                (ASTClassNameNode*)nodes[1],
                (ASTClassBlockNode*)nodes[3],
                (ASTImplementsInterfaceListNode*)nodes[2]
        );
    }

    if (nodes.size() == 4 && nodes.at(0)->is(AST_EXPORT_NODE)) {
        return new ASTClassDeclarationNode(
                (ASTClassNode*)nodes[1],
                (ASTClassNameNode*)nodes[2],
                (ASTClassBlockNode*)nodes[3],
                (ASTExportNode*)nodes[0]
        );
    }

    throw std::invalid_argument("unable to reduce to class declaration since nodes list is not of size 3 or 4");
}