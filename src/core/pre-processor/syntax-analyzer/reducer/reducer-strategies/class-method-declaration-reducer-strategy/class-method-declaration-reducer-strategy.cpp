//
// Created by Johny Georges on 2024-04-21.
//

#include "class-method-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-method-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-method-definition-node.h"

ASTNode* ClassMethodDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() == 3) {
        return new ASTClassMethodDeclarationNode(
                (ASTClassMethodDefinitionNode*)nodes[0],
                (ASTFunctionParameterListNode*)nodes[1],
                (ASTFunctionBlockNode*)nodes[2]
        );
    }

    if (nodes.size() == 4) {
        return new ASTClassMethodDeclarationNode(
                (ASTClassMethodDefinitionNode*)nodes[0],
                (ASTFunctionParameterListNode*)nodes[1],
                (ASTFunctionBlockNode*)nodes[3],
                (ASTTypeNode*)nodes[2]
        );
    }

    throw std::invalid_argument("unable to reduce to class method declaration since nodes list is not of size 4 or 5");
}