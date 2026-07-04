//
// Created by Johny Georges on 2024-04-20.
//

#include "class-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"

std::shared_ptr<ASTNode> ClassDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() == 3) {
        return std::make_shared<ASTClassDeclarationNode>(
                std::dynamic_pointer_cast<ASTClassNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTClassNameNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTClassBlockNode>(nodes[2])
        );
    }

    if (nodes.size() == 4 && nodes.at(2)->is(AST_IMPLEMENTS_INTERFACE_LIST_NODE)) {
        return std::make_shared<ASTClassDeclarationNode>(
                std::dynamic_pointer_cast<ASTClassNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTClassNameNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTClassBlockNode>(nodes[3]),
                std::dynamic_pointer_cast<ASTImplementsInterfaceListNode>(nodes[2])
        );
    }

    if (nodes.size() == 4 && nodes.at(0)->is(AST_EXPORT_NODE)) {
        return std::make_shared<ASTClassDeclarationNode>(
                std::dynamic_pointer_cast<ASTClassNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTClassNameNode>(nodes[2]),
                std::dynamic_pointer_cast<ASTClassBlockNode>(nodes[3]),
                std::dynamic_pointer_cast<ASTExportNode>(nodes[0])
        );
    }

    throw std::invalid_argument("unable to reduce to class declaration since nodes list is not of size 3 or 4");
}